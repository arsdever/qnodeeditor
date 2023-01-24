#include <QList>
#include <QMetaType>

#include "qnodeeditor/qnodeeditor_node.hpp"

#include "qnodeeditor/qnodeeditor.hpp"
#include "qnodeeditor/qnodeeditor_connection.hpp"
#include "qnodeeditor/qnodeeditor_port.hpp"

QNodeEditorNode::QNodeEditorNode() = default;

QNodeEditorNode::QNodeEditorNode(uint64_t id)
    : _id(id)
{
}

QNodeEditorNode::~QNodeEditorNode()
{
    // ingoing connections should be deleted by the nodes they are connected to
    for (auto& connection : _outgoingConnections) {
        connection->_to->_node->_incomingConnections.removeOne(connection);
        delete connection;
    }
    for (auto& port : _inputPorts)
        delete port;
    for (auto& port : _outputPorts)
        delete port;
}

QNodeEditorPort* QNodeEditorNode::createPort(
    PortType type, std::string_view name
)
{
    uint64_t index = 0;
    switch (type) {
        case PortType::In: index = _inputPorts.size(); break;
        case PortType::Out: index = _outputPorts.size(); break;
    }

    auto port = new QNodeEditorPort(this, index, type, name);
    addPort(port);
    return port;
}

void QNodeEditorNode::addPort(QNodeEditorPort* port)
{
    if (port->_type == PortType::In)
        _inputPorts.push_back(port);
    else
        _outputPorts.push_back(port);
}
