#include <QMetaType>

#include "qnodeeditor/qnodeeditor_port.hpp"

#include "qnodeeditor/qnodeeditor.hpp"

QNodeEditorPort::QNodeEditorPort() = default;

QNodeEditorPort::QNodeEditorPort(
    QNodeEditorNode* node, uint64_t index, PortType type, std::string_view name
)
    : _node(node)
    , _index(index)
    , _type(type)
    , _name(name)
{
}
