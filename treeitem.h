#ifndef TREEITEM_H
#define TREEITEM_H

#include "appinfo.h"

#include <QList>
#include <QVariant>

class TreeItem
{
public:
    explicit TreeItem(const QList<QVariant>& data_, TreeItem* parent_ = nullptr);
    ~TreeItem();

    void appendChild(TreeItem* child_);

    TreeItem *child(int row_);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column_) const;
    int row() const;
    TreeItem* parentItem();

private:
    QList<TreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    TreeItem* m_parentItem;
};

#endif // TREEITEM_H
