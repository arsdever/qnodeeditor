#include "qnodeeditor/qnodeeditor_tree.hpp"

#include "qnodeeditor/qnodeeditor.hpp"
#include "qnodeeditor/qnodeeditor_connection.hpp"
#include "qnodeeditor/qnodeeditor_node.hpp"
#include "qnodeeditor/qnodeeditor_port.hpp"

QNodeEditorTree::QNodeEditorTree(QObject* parent)
    : QObject(parent)
{
}

QNodeEditorTree::~QNodeEditorTree()
{
    for (auto& node : _nodes)
        delete node.second;
}

QNodeEditorNode* QNodeEditorTree::addNode()
{
    QNodeEditorNode* node = new QNodeEditorNode { _nodes.size() };
    _nodes.emplace(node->_id, node);
    return node;
}

QNodeEditorConnection* QNodeEditorTree::addConnection(
    uint64_t fromNodeId, uint64_t fromPort, uint64_t toNodeId, uint64_t toPort
)
{
    QNodeEditorNode* fromNode = _nodes.at(fromNodeId);
    QNodeEditorNode* toNode = _nodes.at(toNodeId);

    while (toNode->_inputPorts.size() <= toPort)
        toNode->_inputPorts.push_back(new QNodeEditorPort {
            toNode,
            static_cast<uint64_t>(toNode->_inputPorts.size()),
            PortType::In,
            tr("input %0").arg(toNode->_inputPorts.size()).toStdString() });

    while (fromNode->_outputPorts.size() <= fromPort)
        fromNode->_outputPorts.push_back(new QNodeEditorPort {
            fromNode,
            static_cast<uint64_t>(fromNode->_outputPorts.size()),
            PortType::Out,
            tr("output %0").arg(fromNode->_outputPorts.size()).toStdString() });

    QNodeEditorConnection* connection =
        new QNodeEditorConnection { fromNode->_outputPorts.at(fromPort),
                                    toNode->_inputPorts.at(toPort) };

    fromNode->_outgoingConnections.push_back(connection);

    return connection;
}

QNodeEditorNode* QNodeEditorTree::node(uint64_t id) const
{
    return _nodes.at(id);
}

std::size_t QNodeEditorTree::nodesCount() const { return _nodes.size(); }
