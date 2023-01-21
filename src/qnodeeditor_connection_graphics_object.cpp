#include <QPainter>

#include "qnodeeditor_connection_graphics_object.hpp"

#include "qnodeeditor/qnodeeditor.hpp"
#include "qnodeeditor/qnodeeditor_connection.hpp"
#include "qnodeeditor/qnodeeditor_port.hpp"

QNodeEditorConnectionGraphicsObject::QNodeEditorConnectionGraphicsObject(
    QNodeEditor& editor,
    QNodeEditorConnection* connection,
    QGraphicsItem* parent
)
    : QGraphicsObject(parent)
    , _editor(editor)
    , _connection(connection)
{
    setAcceptHoverEvents(true);
    setZValue(1);
}

QRectF QNodeEditorConnectionGraphicsObject::boundingRect() const
{
    return QRectF(sourcePosition(), targetPosition()).normalized();
}

void QNodeEditorConnectionGraphicsObject::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen({ Qt::black, 5 });
    painter->drawLine(sourcePosition(), targetPosition());

    painter->setPen({ Qt::yellow, 3 });
    painter->drawLine(sourcePosition(), targetPosition());
}

QPointF QNodeEditorConnectionGraphicsObject::sourcePosition() const
{
    return _editor.getPortPosition(_connection->_from);
}

QPointF QNodeEditorConnectionGraphicsObject::targetPosition() const
{
    return _editor.getPortPosition(_connection->_to);
}
