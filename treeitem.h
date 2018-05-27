#ifndef TREEITEM2_H
#define TREEITEM2_H


#include "appinfo.h"

#include <QString>
#include <QVariant>
#include <QList>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QFileInfoList>

class TreeItem
{
public:

    enum class treeType
    {
        root,
        directory,
        file,
        function,
        variable,
        enumeration,
        macros,

        size
    };

    explicit TreeItem(treeType type, const QVariant& data, TreeItem* parent = nullptr);
    ~TreeItem();

    void setData(const QVariant& data);
    QVariant data() const;

    void appendChild(TreeItem* child);
    TreeItem* child(int row);
    int childCount() const;

    TreeItem* paremtItem();
    int row() const;

    QString typeIconPath() const;

    treeType type() const;
    void setFlagHeader();
    void setFlagSource();
    QString path() const;

private:

    void setData();

    static QList<QString> m_type_icon_path;

    TreeItem* m_parentItem;
    QVariant m_data;
    QList<TreeItem*> m_childItem;

    treeType m_type;
    QString m_path;
    bool m_flag_header_file;
    bool m_flag_source_file;

};

#endif // TREEITEM2_H
