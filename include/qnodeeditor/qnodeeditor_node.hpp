#pragma once

class QNodeEditorConnection;
class QNodeEditorPort;
enum class PortType;

class QNodeEditorNode
{
public:
    QNodeEditorNode();
    QNodeEditorNode(uint64_t id);
    ~QNodeEditorNode();

    QNodeEditorPort* createPort(PortType type, std::string_view name);

    void addPort(QNodeEditorPort* port);

public:
    uint64_t _id;
    // TODO remove later
    uint64_t _rank;
    QList<QNodeEditorConnection*> _incomingConnections;
    QList<QNodeEditorConnection*> _outgoingConnections;
    QList<QNodeEditorPort*> _inputPorts;
    QList<QNodeEditorPort*> _outputPorts;
};

Q_DECLARE_METATYPE(QNodeEditorNode)
