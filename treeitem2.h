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

class TreeItem2
{
public:
#ifdef  TASK_0_0_3_003
    enum class treeType
    {
        root,
        directory,
        file
    };

    explicit TreeItem2(treeType type, const QVariant& data, TreeItem2* parent = nullptr);

#else
    explicit TreeItem2(const QVariant& data, TreeItem2* parent = nullptr);
#endif//TASK_0_0_3_003
    ~TreeItem2();

    void setData(const QVariant& data);
    QVariant data() const;

    void appendChild(TreeItem2* child);
    TreeItem2* child(int row);
    int childCount() const;

    TreeItem2* paremtItem();
    int row() const;

#ifdef TASK_0_0_3_003
    treeType type() const;
    void setFlagHeader();
    void setFlagSource();
    QString path() const;
#endif

private:

#ifdef  TASK_0_0_3_003
    void setData();
#endif

    TreeItem2* m_parentItem;
    QVariant m_data;
    QList<TreeItem2*> m_childItem;

#ifdef  TASK_0_0_3_003
    treeType m_type;
    QString m_path;
    bool m_flag_header_file;
    bool m_flag_source_file;
#endif

};

#endif // TREEITEM2_H
