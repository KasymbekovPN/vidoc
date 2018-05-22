#include "treeitem2.h"

#ifdef  TASK_0_0_3_003
TreeItem2::TreeItem2(TreeItem2::treeType type, const QVariant &data, TreeItem2 *parent)
    : m_type(type), m_parentItem(parent)
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
#else
TreeItem2::TreeItem2(const QVariant &data, TreeItem2 *parent)
    : m_data(data), m_parentItem(parent)
{
}
#endif

TreeItem2::~TreeItem2()
{
    delete m_parentItem;
    qDeleteAll(m_childItem);
}

void TreeItem2::setData(const QVariant &data)
{
    m_data = data;
}

QVariant TreeItem2::data() const
{
    return m_data;
}

void TreeItem2::appendChild(TreeItem2 *child)
{
    m_childItem.append(child);
}

TreeItem2 *TreeItem2::child(int row)
{
    return m_childItem.value(row);
}

int TreeItem2::childCount() const
{
    return m_childItem.count();
}

TreeItem2 *TreeItem2::paremtItem()
{
    return m_parentItem;
}

int TreeItem2::row() const
{
    return (m_parentItem
            ? m_parentItem->m_childItem.indexOf(const_cast<TreeItem2*>(this))
            : 0);
}

TreeItem2::treeType TreeItem2::type() const
{
    return m_type;
}

void TreeItem2::setFlagHeader()
{
    m_flag_header_file = true;
}

void TreeItem2::setFlagSource()
{
    m_flag_source_file = true;
}

QString TreeItem2::path() const
{
    return m_path;
}

void TreeItem2::setData()
{
#ifdef  TASK_0_0_3_004

    QDir dir = m_path;
    dir.setSorting(QDir::DirsFirst | QDir::Name | QDir::IgnoreCase);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);

    QFileInfoList infoList = dir.entryInfoList();
    foreach (QFileInfo fileInfo, infoList) {
        if (fileInfo.isDir())
        {
            this->appendChild(new TreeItem2(
                                  TreeItem2::treeType::directory,
                                  QVariant(fileInfo.filePath()),
                                  this
                                  ));
        }
        else if (fileInfo.isFile() &&
                 ("h" == fileInfo.suffix() || "c" == fileInfo.suffix()))
        {
            bool need_append = true;
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

            if (need_append)
            {
                this->appendChild(new TreeItem2(
                                      TreeItem2::treeType::file,
                                      QVariant(fileInfo.filePath()),
                                      this
                                      ));
            }
        }
    }
#endif//TASK_0_0_3_004
}

