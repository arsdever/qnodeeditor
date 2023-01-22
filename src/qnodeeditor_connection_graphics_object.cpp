#include <QPainter>
#include <QPainterPath>

#include "qnodeeditor_connection_graphics_object.hpp"

#include "qnodeeditor/qnodeeditor.hpp"
#include "qnodeeditor/qnodeeditor_connection.hpp"
#include "qnodeeditor/qnodeeditor_port.hpp"

namespace
{
static constexpr double ARC_DIAMETER = 20;
} // namespace

QNodeEditorConnectionGraphicsObject::QNodeEditorConnectionGraphicsObject(
    QNodeEditor& editor,
    QNodeEditorConnection* connection,
    QGraphicsItem* parent
)
    : QGraphicsObject(parent)
    , _editor(editor)
    , _connection(connection)
    , _state(QStyle::State_None)
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

    QPainterPath path;
    path.moveTo(sourcePosition());
    if (sourcePosition().x() == targetPosition().x()) {
        path.lineTo(targetPosition());
    } else {
        // draw horizontal line from source to the middle
        // continue with arc to a vertical line
        // continue with arc to a horizontal line untli the target
        double diameter = std::min(
            ARC_DIAMETER,
            std::min(boundingRect().width(), boundingRect().height())
        );
        path.lineTo(
            sourcePosition().x() + boundingRect().width() / 2.0 -
                diameter / 2.0,
            sourcePosition().y()
        );
        path.arcTo(
            QRectF { sourcePosition().x() + boundingRect().width() / 2.0 -
                         diameter,
                     sourcePosition().y() - diameter,
                     diameter,
                     diameter },
            270,
            90
        );
        path.lineTo(
            sourcePosition().x() + boundingRect().width() / 2.0,
            targetPosition().y() + diameter / 2.0
        );
        path.arcTo(
            QRectF { sourcePosition().x() + boundingRect().width() / 2.0,
                     targetPosition().y(),
                     diameter,
                     diameter },
            180,
            -90
        );
        path.lineTo(targetPosition());
    }

    painter->setPen(QPen { Qt::black, 5 });
    painter->drawPath(path);
    painter->setPen(QPen { Qt::yellow,
                           (_state & QStyle::State_MouseOver) ? 4.0 : 2.0 });
    painter->drawPath(path);
}

void QNodeEditorConnectionGraphicsObject::hoverEnterEvent(
    QGraphicsSceneHoverEvent* event
)
{
    _state |= QStyle::State_MouseOver;
    update();
    QGraphicsObject::hoverEnterEvent(event);
}

void QNodeEditorConnectionGraphicsObject::hoverLeaveEvent(
    QGraphicsSceneHoverEvent* event
)
{
    _state &= ~QStyle::State_MouseOver;
    update();
    QGraphicsObject::hoverLeaveEvent(event);
}

QPointF QNodeEditorConnectionGraphicsObject::sourcePosition() const
{
    return _editor.getPortPosition(_connection->_from);
}

QPointF QNodeEditorConnectionGraphicsObject::targetPosition() const
{
    return _editor.getPortPosition(_connection->_to);
}
