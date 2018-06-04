#include "treeitem.h"

QList<QString> TreeItem::m_type_icon_path = {"",
                                          ":/img/dir.png",
                                          ":/img/c-lang-icon.png",
                                          ":/img/func-icon.png",
                                          ":/img/var-icon.png"
                                          ":/img/macro-icon.png",
                                          ":/img/enum-icon.png"
                                         };

TreeItem::TreeItem(TreeItem::treeType type, const QVariant &data, shared_ptr<QList<QString>> ignored_files, TreeItem *parent)
    : m_type(type), m_parentItem(parent), m_ignored_files(ignored_files)
{
    switch(m_type)
    {
    case treeType::root:
        m_data = data;
        break;
    case treeType::file:
    {
        m_path = data.toString();
        QFileInfo fi = QFileInfo(m_path);
        m_data = QVariant(fi.baseName());
    }  break;
    case treeType::directory:
    {
        m_path = data.toString();
        QFileInfo fi = QFileInfo(m_path);
        m_data = QVariant(fi.baseName());

        setData();
    }  break;
    default:
        break;
    }
}

TreeItem::~TreeItem()
{
    delete m_parentItem;
    qDeleteAll(m_childItem);
}

void TreeItem::setData(const QVariant &data)
{
    m_data = data;
}

QVariant TreeItem::data() const
{
    return m_data;
}

void TreeItem::appendChild(TreeItem *child)
{
    m_childItem.append(child);
}

TreeItem *TreeItem::child(int row)
{
    return m_childItem.value(row);
}

int TreeItem::childCount() const
{
    return m_childItem.count();
}

TreeItem *TreeItem::paremtItem()
{
    return m_parentItem;
}

int TreeItem::row() const
{
    return (m_parentItem
            ? m_parentItem->m_childItem.indexOf(const_cast<TreeItem*>(this))
            : 0);
}

QString TreeItem::typeIconPath() const
{
    treeType type = treeType::size <= m_type ? treeType::root : m_type;
    return m_type_icon_path[int(type)];
}

TreeItem::treeType TreeItem::type() const
{
    return m_type;
}

void TreeItem::setFlagHeader()
{
    m_flag_header_file = true;
}

void TreeItem::setFlagSource()
{
    m_flag_source_file = true;
}

QString TreeItem::path() const
{
    return m_path;
}

#ifdef  TASK_0_0_4__6
void TreeItem::clear()
{
//    m_parentItem = nullptr;
    m_data.clear();
    m_childItem.clear();
//    treeType m_type;
//    QString m_path;
//    bool m_flag_header_file;
//    bool m_flag_source_file;
}
#endif//TASK_0_0_4__6

void TreeItem::setData()
{

    QDir dir = m_path;
    dir.setSorting(QDir::DirsFirst | QDir::Name | QDir::IgnoreCase);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);

    QFileInfoList infoList = dir.entryInfoList();
    foreach (QFileInfo fileInfo, infoList) {
        if (fileInfo.isDir())
        {
            this->appendChild(new TreeItem(
                                  TreeItem::treeType::directory,
                                  QVariant(fileInfo.filePath()),
                                  m_ignored_files,
                                  this
                                  ));
        }
        else if (fileInfo.isFile() &&
                 ("h" == fileInfo.suffix() || "c" == fileInfo.suffix()))
        {
            bool need_append = true;

            for(auto ignored_file_name: *m_ignored_files)
            {
                if (ignored_file_name == fileInfo.filePath())
                {
                    need_append = false;
                }
            }

            if (need_append)
            {
                for(int i = 0; i < this->childCount(); ++i)
                {
                    QFileInfo fi = QFileInfo(this->child(i)->path());

                    if (fi.baseName() == fileInfo.baseName())
                    {
                        need_append = false;
                        if ("h" == fileInfo.suffix())
                        {
                            this->child(i)->setFlagHeader();
                        }
                        else
                        {
                            this->child(i)->setFlagSource();
                        }
                    }
                }
            }

            if (need_append)
            {
                this->appendChild(new TreeItem(
                                      TreeItem::treeType::file,
                                      QVariant(fileInfo.filePath()),
                                      m_ignored_files,
                                      this
                                      ));
            }
        }
    }
}

