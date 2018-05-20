#include "treeitem2.h"

TreeItem2::TreeItem2(const QVariant &data, TreeItem2 *parent)
    : m_data(data), m_parentItem(parent)
{
}

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

