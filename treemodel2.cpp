#include "treemodel2.h"

TreeModel2::TreeModel2(QObject *parent)
{
    QVariant rootItem = tr("Заголовок");
    m_rootItem = new TreeItem2(rootItem);

//    m_rootItem->appendChild(new TreeItem2(QVariant("1"), m_rootItem));
//    m_rootItem->appendChild(new TreeItem2(QVariant("2"), m_rootItem));
//    m_rootItem->appendChild(new TreeItem2(QVariant("3"), m_rootItem));
//    m_rootItem->appendChild(new TreeItem2(QVariant("4"), m_rootItem));

//    m_rootItem->child(0)->appendChild(new TreeItem2(QVariant("1_1"),
//                                                    m_rootItem->child(0)));

//    qDebug() << m_rootItem->childCount();
}

TreeModel2::~TreeModel2()
{
    delete m_rootItem;
}

QVariant TreeModel2::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || Qt::DisplayRole != role)
    {
        return QVariant();
    }

//    return QVariant();
    TreeItem2* item = static_cast<TreeItem2*>(index.internalPointer());
    return item->data();
}

Qt::ItemFlags TreeModel2::flags(const QModelIndex &index) const
{
    return (index.isValid()
            ? QAbstractItemModel::flags(index)
            : 0);
}

QVariant TreeModel2::headerData(int section, Qt::Orientation orientation, int role) const
{
    return (Qt::Horizontal == orientation && Qt::DisplayRole == role
            ? m_rootItem->data()
            : QVariant());
}

QModelIndex TreeModel2::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

//    return QModelIndex();
    TreeItem2* parentItem;
    parentItem = parent.isValid()
            ?static_cast<TreeItem2*>(parent.internalPointer())
           : m_rootItem;

    TreeItem2* childItem = parentItem->child(row);
    return (childItem
            ? createIndex(row, column, childItem)
            : QModelIndex());
}

QModelIndex TreeModel2::parent(const QModelIndex &child) const
{
    if (!child.isValid())
    {
        return QModelIndex();
    }

//    return QModelIndex();
    TreeItem2* childItem = static_cast<TreeItem2*>(child.internalPointer());
    TreeItem2* parentItem = childItem->paremtItem();

    return (parentItem == m_rootItem
            ? QModelIndex()
            : createIndex(parentItem->row(), 0, parentItem));
}

int TreeModel2::rowCount(const QModelIndex &parent) const
{
    if (0 < parent.column())
    {
        return 0;
    }

//    return 0;
    TreeItem2* parentItem = (parent.isValid()
                             ? static_cast<TreeItem2*>(parent.internalPointer())
                             : m_rootItem);

    return parentItem->childCount();
}

int TreeModel2::columnCount(const QModelIndex &parent) const
{
    return 1;
}

void TreeModel2::setConfig(const QJsonObject &config)
{

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
            m_ignored_files.append(filePath);
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

void TreeModel2::setData()
{
    QDir dir = m_source_dir;
    dir.setSorting(QDir::DirsFirst | QDir::Name | QDir::IgnoreCase);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
    QFileInfoList infoList = dir.entryInfoList();

    foreach (QFileInfo fileInfo, infoList) {
        m_rootItem->appendChild(new TreeItem2(QVariant(fileInfo.fileName()), m_rootItem));
    }
}
