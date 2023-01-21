#pragma once

#include <QAbstractListModel>
#include <unordered_map>

#include "qnodeeditor/qnodeeditor_port.hpp"

Q_DECLARE_METATYPE(std::shared_ptr<QNodeEditorPort>)
class QNodeEditorConnection;

class QNodeEditorTreeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum NodeDataRole {
        NodeId = Qt::UserRole,
        Connections,
        Color,
        Inputs,
        Outputs,
    };

public:
    explicit QNodeEditorTreeModel(QObject* parent = nullptr);
    ~QNodeEditorTreeModel() override;

    uint64_t addNode();
    void addConnection(
        uint64_t fromNodeId,
        uint64_t fromPort,
        uint64_t toNodeId,
        uint64_t toPort
    );

#pragma region QAbstractItemModel
    QModelIndex index(
        int row, int column = 0, const QModelIndex& parent = QModelIndex {}
    ) const override;
    int rowCount(const QModelIndex& parent = QModelIndex {}) const override;
    int columnCount(const QModelIndex& parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role)
        const override;
#pragma endregion

signals:
    void nodeAdded(QModelIndex index);
    void connectionAdded(QNodeEditorConnection* connection);

private:
    QNodeEditorNode* _root;
    std::unordered_map<uint64_t, QNodeEditorNode*> _nodes;

    static uint64_t idCounter;
};
