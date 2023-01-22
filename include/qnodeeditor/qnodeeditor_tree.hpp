#pragma once

#include <QObject>

class QNodeEditorNode;
class QNodeEditorConnection;

class QNodeEditorTree : public QObject
{
public:
    explicit QNodeEditorTree(QObject* parent = nullptr);
    ~QNodeEditorTree();

    QNodeEditorNode* addNode();
    QNodeEditorConnection* addConnection(
        uint64_t fromNodeId,
        uint64_t fromPort,
        uint64_t toNodeId,
        uint64_t toPort
    );

    QNodeEditorNode* node(uint64_t id) const;
    bool forEachNode(std::function<bool(QNodeEditorNode*)> callback) const;

    std::size_t nodesCount() const;

private:
    std::unordered_map<uint64_t, QNodeEditorNode*> _nodes;
};
