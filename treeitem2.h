#ifndef TREEITEM2_H
#define TREEITEM2_H


#include "appinfo.h"

#include <QString>
#include <QVariant>
#include <QList>

class TreeItem2
{
public:
    explicit TreeItem2(const QVariant& data, TreeItem2* parent = nullptr);
    ~TreeItem2();

    void setData(const QVariant& data);
    QVariant data() const;

    void appendChild(TreeItem2* child);
    TreeItem2* child(int row);
    int childCount() const;

    TreeItem2* paremtItem();
    int row() const;

private:
    TreeItem2* m_parentItem;
    QVariant m_data;
    QList<TreeItem2*> m_childItem;

};

#endif // TREEITEM2_H
