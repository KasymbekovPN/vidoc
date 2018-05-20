#ifndef TREEMODEL2_H
#define TREEMODEL2_H

#include "appinfo.h"
#include "treeitem2.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QString>
#include <QDebug>
#include <QJsonObject>
#include <QList>
#include <QJsonArray>
#include <QMessageBox>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>

class TreeItem2;

class TreeModel2 : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TreeModel2(QObject* parent = nullptr);
    ~TreeModel2();

    QVariant data(const QModelIndex& index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void setConfig(const QJsonObject& config);

private:

    void setData();

    TreeItem2* m_rootItem;
    QString m_source_dir;
    QString m_output_dir;
    QList<QString> m_ignored_files;
};

#endif // TREEMODEL2_H
