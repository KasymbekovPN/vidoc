#include "treemodel.h"

TreeModel::TreeModel(QObject *parent)
{
    QVariant rootItem = tr("Заголовок");
    QList<QString> tmp;
    m_ignored_files = std::make_shared<QList<QString>>(QList<QString>());

    m_rootItem = new TreeItem(TreeItem::treeType::root, rootItem, m_ignored_files);
}

TreeModel::~TreeModel()
{
    delete m_rootItem;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
    {
        return QVariant();
    }

    switch(role)
    {
    case Qt::DisplayRole:
    {
        TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
        return item->data();
    }  break;
    case Qt::DecorationRole:
    {
        TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
        return QIcon(item->typeIconPath());
     }   break;
    default:
        break;
    }

    return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    return (index.isValid()
            ? QAbstractItemModel::flags(index)
            : 0);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return (Qt::Horizontal == orientation && Qt::DisplayRole == role
            ? m_rootItem->data()
            : QVariant());
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    TreeItem* parentItem;
    parentItem = parent.isValid()
            ?static_cast<TreeItem*>(parent.internalPointer())
           : m_rootItem;

    TreeItem* childItem = parentItem->child(row);
    return (childItem
            ? createIndex(row, column, childItem)
            : QModelIndex());
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
    {
        return QModelIndex();
    }

    TreeItem* childItem = static_cast<TreeItem*>(child.internalPointer());
    TreeItem* parentItem = childItem->paremtItem();

    return (parentItem == m_rootItem
            ? QModelIndex()
            : createIndex(parentItem->row(), 0, parentItem));
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (0 < parent.column())
    {
        return 0;
    }

    TreeItem* parentItem = (parent.isValid()
                             ? static_cast<TreeItem*>(parent.internalPointer())
                             : m_rootItem);

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

void TreeModel::setConfig(const QJsonObject &config, const QString& target_name)
{

    m_rootItem->setData(QVariant(target_name));

    //
    // Получаем из конфигурацимонного файла цели путь
    // директории с исходнимами; проверяем - существует ли
    // директория.
    //
    m_source_dir = config["source-dir"].toString();
    QDir source_dir = m_source_dir;
    if (!source_dir.exists() || m_source_dir.isEmpty())
    {
        QMessageBox::critical(nullptr, tr("Ошибка"),
                              tr("Входная директория : \"") + m_source_dir + tr("\" не существует"));

        m_source_dir.clear();
        return;
    }

    //
    // Получаем из конфигурационного файла цели путь
    // выходной директории; проверяем - существует ли
    // директория.
    //
    m_output_dir = config["output-dir"].toString();
    QDir output_dir = m_output_dir;
    if (!output_dir.exists() || m_output_dir.isEmpty())
    {
        QMessageBox::critical(nullptr, tr("Ошибка"),
                              tr("Выходная директория : \"") + m_source_dir + tr("\" не существует"));

        m_output_dir.clear();
        return;
    }

    //
    // Получаем из конфигурационного файла цели список
    // игнорируемых файлов; проверям - существуют ли файлы.
    //
    QList<QVariant> lst = config["ignored-files"].toArray().toVariantList();
    QList<QString> nonexist_file;
    QFileInfo fileInfo;
    foreach (QVariant vStr, lst) {

        QString filePath = vStr.toString();
        fileInfo = filePath;
        if (fileInfo.exists() && fileInfo.isFile())
        {
            m_ignored_files.get()->append(filePath);
        }
        else
        {
            nonexist_file.append(filePath);
        }
    }

    if (!nonexist_file.isEmpty())
    {
        QString msg = tr("Следующие файлы, отмеченные как игнорируемые, не существуют:");
        foreach (auto name, nonexist_file) {
            msg += "\n" + name;
        }
        QMessageBox::warning(nullptr, tr("Внимание"), msg);
    }

    setData();
}

void TreeModel::setData()
{

    QDir dir = m_source_dir;
    dir.setSorting(QDir::DirsFirst | QDir::Name | QDir::IgnoreCase);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
    QFileInfoList infoList = dir.entryInfoList();

    foreach (QFileInfo fileInfo, infoList)
    {
        if (fileInfo.isDir())
        {
            m_rootItem->appendChild(new TreeItem(
                                        TreeItem::treeType::directory,
                                        QVariant(fileInfo.filePath()),
                                        m_ignored_files,
                                        m_rootItem
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
                    break;
                }
            }

            if (need_append)
            {
                for(int i = 0; i < m_rootItem->childCount(); ++i)
                {
                    QFileInfo fi = QFileInfo(m_rootItem->child(i)->path());

                    if (fi.baseName() == fileInfo.baseName())
                    {
                        need_append = false;
                        if ("h" == fileInfo.suffix())
                        {
                                m_rootItem->child(i)->setFlagHeader();
                        }
                        else
                        {
                            m_rootItem->child(i)->setFlagSource();
                        }
                    }
                }
            }

            if (need_append)
            {
                m_rootItem->appendChild(new TreeItem(
                                            TreeItem::treeType::file,
                                            QVariant(fileInfo.filePath()),
                                            m_ignored_files,
                                            m_rootItem
                                            ));
            }
        }
    }
}
