#include <QMetaType>

#include "qnodeeditor/qnodeeditor_connection.hpp"

#include "qnodeeditor/qnodeeditor.hpp"

QNodeEditorConnection::QNodeEditorConnection() = default;

QNodeEditorConnection::QNodeEditorConnection(
    QNodeEditorPort* from, QNodeEditorPort* to
)
    : _from(from)
    , _to(to)
{
}
