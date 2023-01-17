#pragma once

#include <QAbstractItemModel>

class QNodeEditorTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum NodeDataRole {
        NodeId = Qt::UserRole,
        Connections = Qt::UserRole + 1,
    };

public:
    explicit QNodeEditorTreeModel(QObject* parent = nullptr);
    ~QNodeEditorTreeModel() override;

#pragma region QAbstractItemModel
    QModelIndex index(int row, int column, const QModelIndex& parent)
        const override;
    QModelIndex parent(const QModelIndex& child) const override;
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role)
        override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role)
        const override;
#pragma endregion
};
