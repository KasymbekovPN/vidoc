#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "treeitem.h"
#include "appinfo.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QDebug>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TreeModel(const QString& data_, QObject* parent_ = nullptr);
#ifdef  TASK_0_0_3_001
    explicit TreeModel(QObject* parent = nullptr);
#endif
    ~TreeModel();

    QVariant data(const QModelIndex& index_, int role_) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section_, Qt::Orientation orientation_,
                        int role_ = Qt::DisplayRole) const override;
    QModelIndex index(int row_, int column_,
                      const QModelIndex& parent_ = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index_) const override;
    int rowCount(const QModelIndex& parent_ = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent_ = QModelIndex()) const override;

#ifdef  TASK_0_0_3_001
    void setData(const QString& data);
#endif

private:
    void setupModelData(const QStringList& lines, TreeItem* parent_);

    /*!
     * \brief m_rootItem - корневой элемент
     */
    TreeItem* m_rootItem;
};

#endif // TREEMODEL_H
