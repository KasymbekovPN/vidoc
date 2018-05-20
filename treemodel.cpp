#include "treemodel.h"
#include "treeitem.h"

#include <QStringList>

/*!
 * \brief TreeModel::TreeModel
 * \param data_ - инициализирующие данные
 * \param parent_ - родитель.
 */
TreeModel::TreeModel(const QString &data_, QObject *parent_)
    :QAbstractItemModel(parent_)
{
    QList<QVariant> rootData;
#ifdef  TASK_0_0_3_001
    rootData << tr("Здесь будет какой-то заголовок, например, имя цели");
#else
    rootData << "Title" << "Summary";
#endif
    m_rootItem = new TreeItem(rootData);

#ifndef  TASK_0_0_3_001
    setupModelData(data_.split("\n"), m_rootItem);
#endif

    QList<QVariant> lst;
    lst << "1";
    m_rootItem->appendChild(new TreeItem(lst, m_rootItem));

    lst.clear();
    lst << "2" << "3";
    m_rootItem->appendChild(new TreeItem(lst, m_rootItem));

    lst.clear();
    lst << "2_1";
    m_rootItem->child(0)->appendChild(new TreeItem(lst, m_rootItem->child(0)));
}

#ifdef  TASK_0_0_3_001
TreeModel::TreeModel(QObject *parent)
    :QAbstractItemModel(parent)
{

}
#endif

TreeModel::~TreeModel()
{
    delete m_rootItem;
}

QVariant TreeModel::data(const QModelIndex &index_, int role_) const
{
    if (!index_.isValid() || Qt::DisplayRole != role_)
    {
        return QVariant();
    }

    TreeItem* item = static_cast<TreeItem*>(index_.internalPointer());

    return item->data(index_.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    return (index.isValid()
            ? QAbstractItemModel::flags(index)
            : 0);
}

QVariant TreeModel::headerData(int section_, Qt::Orientation orientation_, int role_) const
{

    return (Qt::Horizontal == orientation_ && Qt::DisplayRole == role_
            ? m_rootItem->data(section_)
            : QVariant());
}

QModelIndex TreeModel::index(int row_, int column_, const QModelIndex &parent_) const
{

    if (!hasIndex(row_, column_, parent_))
    {
        return QModelIndex();
    }

    TreeItem* parentItem;
    parentItem = parent_.isValid()
            ? static_cast<TreeItem*>(parent_.internalPointer())
            : m_rootItem;

    TreeItem* childItem = parentItem->child(row_);

    return (childItem
            ? createIndex(row_, column_, childItem)
            : QModelIndex());
}

QModelIndex TreeModel::parent(const QModelIndex &index_) const
{
    if (!index_.isValid())
    {
        return QModelIndex();
    }

    TreeItem* childItem = static_cast<TreeItem*>(index_.internalPointer());
    TreeItem* parentItem = childItem->parentItem();

    if (parentItem == m_rootItem)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent_) const
{
    TreeItem* parentItem;
    if (0 < parent_.column())
    {
        return 0;
    }

    parentItem = (parent_.isValid()
                  ? static_cast<TreeItem*>(parent_.internalPointer())
                  : m_rootItem);

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent_) const
{
    return (parent_.isValid()
            ? static_cast<TreeItem*>(parent_.internalPointer())->columnCount()
            : m_rootItem->columnCount());
}

void TreeModel::setData(const QString &data)
{
    setupModelData(data.split("\n"), m_rootItem);
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent_)
{

//    qDebug() << lines;

    QList<TreeItem*> parents;
    QList<int> indecations;
    parents << parent_;
    indecations << 0;

    int number = 0;

    while (number < lines.count())
    {
        int position = 0;
        while(position < lines[number].length())
        {
            if (' ' != lines[number].at(position))
            {
                break;
            }

            position++;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty())
        {
            QStringList columnString = lineData.split("\t", QString::SkipEmptyParts);
            QList<QVariant> columnData;
            for(int column = 0; column < columnString.count(); ++column)
            {
                columnData << columnString[column];
            }

            if (position > indecations.last())
            {
                if (parents.last()->childCount() > 0)
                {
                    parents << parents.last()->child(parents.last()->childCount() - 1);
                    indecations << position;
                }
            }
            else
            {
                while(position < indecations.last() && parents.count() > 0)
                {
                    parents.pop_back();
                    indecations.pop_back();
                }
            }

            parents.last()->appendChild(new TreeItem(columnData, parents.last()));
        }

        ++number;
    }
}
