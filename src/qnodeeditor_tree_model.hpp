#pragma once

#include <QAbstractListModel>
#include <unordered_map>

#include "qnodeeditor/qnodeeditor_port.hpp"

Q_DECLARE_METATYPE(std::shared_ptr<QNodeEditorPort>)
class QNodeEditorConnection;
class QNodeEditorTree;

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

    QNodeEditorNode* addNode();
    QNodeEditorConnection* addConnection(
        uint64_t fromNodeId,
        uint64_t fromPort,
        uint64_t toNodeId,
        uint64_t toPort
    );

    void setTree(QNodeEditorTree* tree);
    QNodeEditorTree* tree() const;

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
    QNodeEditorTree* _tree;

    static uint64_t idCounter;
};
