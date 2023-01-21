#pragma once

#include <QAbstractListModel>
#include <unordered_map>

#include "qnodeeditor/qnodeeditor_port.hpp"

struct QNodeEditorNode {
    uint64_t id;
    std::vector<QNodeEditorNode*> connections;
    QList<std::shared_ptr<QNodeEditorPort>> inputPorts;
    QList<std::shared_ptr<QNodeEditorPort>> outputPorts;
};

Q_DECLARE_METATYPE(QNodeEditorNode*)
Q_DECLARE_METATYPE(std::shared_ptr<QNodeEditorPort>)

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
    void addConnection(uint64_t from, uint64_t to);

#pragma region QAbstractItemModel
    int rowCount(const QModelIndex& parent = QModelIndex {}) const override;
    int columnCount(const QModelIndex& parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role)
        const override;
#pragma endregion

signals:
    void nodeAdded(QModelIndex index);
    void connectionAdded(QModelIndex from, QModelIndex to);

private:
    QNodeEditorNode* _root;
    std::unordered_map<uint64_t, QNodeEditorNode*> _nodes;

    static uint64_t idCounter;
};
