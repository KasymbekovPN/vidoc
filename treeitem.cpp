#include "treeitem.h"

#include <QStringList>

TreeItem::TreeItem(const QList<QVariant> &data_, TreeItem *parent_)
{
    m_parentItem = parent_;
    m_itemData = data_;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *child_)
{
    m_childItems.append(child_);
}

TreeItem *TreeItem::child(int row_)
{
    return m_childItems.value(row_);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    return m_itemData.count();
}

QVariant TreeItem::data(int column_) const
{
    return m_itemData.value(column_);
}

int TreeItem::row() const
{
    return ( m_parentItem
             ? m_parentItem ->m_childItems.indexOf(const_cast<TreeItem*>(this))
             : 0);
}

TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}
