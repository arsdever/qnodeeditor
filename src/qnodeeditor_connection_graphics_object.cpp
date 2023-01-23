#include <QPainter>
#include <QPainterPath>

#include "qnodeeditor_connection_graphics_object.hpp"

#include "qnodeeditor/qnodeeditor.hpp"
#include "qnodeeditor/qnodeeditor_connection.hpp"
#include "qnodeeditor/qnodeeditor_port.hpp"

namespace
{
// check the shape when changing the ARC_DIAMETER
static constexpr double SHAPE_CLEARANCE = 5;
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
    QPointF sp = sourcePosition();
    QPointF tp = targetPosition();
    recalculateDrawingShape(sp, tp);
    recalculateShape(sp, tp);
    _cachedSourcePosition = sp;
    _cachedTargetPosition = tp;

    setAcceptHoverEvents(true);
    setZValue(1);
}

QRectF QNodeEditorConnectionGraphicsObject::boundingRect() const
{
    return QRectF(sourcePosition(), targetPosition())
        .normalized()
        .adjusted(
            -SHAPE_CLEARANCE, -SHAPE_CLEARANCE, SHAPE_CLEARANCE, SHAPE_CLEARANCE
        );
}

void QNodeEditorConnectionGraphicsObject::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
)
{
    QPointF sp = sourcePosition();
    QPointF tp = targetPosition();

    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing, true);

    if (sourcePosition() != _cachedSourcePosition ||
        targetPosition() != _cachedTargetPosition) {
        recalculateDrawingShape(sp, tp);
        recalculateShape(sp, tp);
        _cachedSourcePosition = sp;
        _cachedTargetPosition = tp;
    }

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(6);
    pen.setCapStyle(Qt::RoundCap);

    painter->setPen(pen);
    painter->drawPath(_drawShape);

    pen.setColor(Qt::yellow);
    pen.setWidth((_state & QStyle::State_MouseOver) ? 4.0 : 2.0);

    painter->setPen(pen);
    painter->drawPath(_drawShape);

    // for debugging
    // painter->setPen(QPen { Qt::red, 1.0 });
    // painter->drawPath(_shape);
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

QPainterPath QNodeEditorConnectionGraphicsObject::shape() const
{
    QPointF sp = sourcePosition();
    QPointF tp = targetPosition();

    recalculateDrawingShape(sp, tp);
    recalculateShape(sp, tp);

    _cachedSourcePosition = sp;
    _cachedTargetPosition = tp;
    return _shape;
}

QPointF QNodeEditorConnectionGraphicsObject::sourcePosition() const
{
    return _editor.getPortPosition(_connection->_from);
}

QPointF QNodeEditorConnectionGraphicsObject::targetPosition() const
{
    return _editor.getPortPosition(_connection->_to);
}

void QNodeEditorConnectionGraphicsObject::recalculateShape(
    QPointF sourcePoint, QPointF targetPoint
) const
{
    if (sourcePoint != _cachedSourcePosition ||
        targetPoint != _cachedTargetPosition) {
        _shape.clear();
        _shape.moveTo(
            sourcePoint.x() + SHAPE_CLEARANCE, sourcePoint.y() + SHAPE_CLEARANCE
        );
        if (sourcePoint.x() == targetPoint.x() ||
            sourcePoint.y() == targetPoint.y()) {
            _shape.lineTo(
                targetPoint.x() - SHAPE_CLEARANCE,
                targetPoint.y() + SHAPE_CLEARANCE
            );
            _shape.lineTo(
                targetPoint.x() - SHAPE_CLEARANCE,
                targetPoint.y() - SHAPE_CLEARANCE
            );
            _shape.lineTo(
                sourcePoint.x() + SHAPE_CLEARANCE,
                sourcePoint.y() - SHAPE_CLEARANCE
            );
        } else {
            QPointF centerPoint = QPointF(
                (sourcePoint.x() + targetPoint.x()) / 2.0,
                (sourcePoint.y() + targetPoint.y()) / 2.0
            );
            _shape.cubicTo(
                centerPoint.x(),
                sourcePoint.y() + SHAPE_CLEARANCE,
                centerPoint.x(),
                targetPoint.y() + SHAPE_CLEARANCE,
                targetPoint.x() - SHAPE_CLEARANCE,
                targetPoint.y() + SHAPE_CLEARANCE
            );
            _shape.lineTo(
                targetPoint.x() - SHAPE_CLEARANCE,
                targetPoint.y() - SHAPE_CLEARANCE
            );
            _shape.cubicTo(
                centerPoint.x(),
                targetPoint.y() - SHAPE_CLEARANCE,
                centerPoint.x(),
                sourcePoint.y() - SHAPE_CLEARANCE,
                sourcePoint.x() + SHAPE_CLEARANCE,
                sourcePoint.y() - SHAPE_CLEARANCE
            );
        }
    }
}
void QNodeEditorConnectionGraphicsObject::recalculateDrawingShape(
    QPointF sourcePoint, QPointF targetPoint
) const
{
    if (sourcePoint != _cachedSourcePosition ||
        targetPoint != _cachedTargetPosition) {
        _drawShape.clear();
        _drawShape.moveTo(sourcePoint);
        if (sourcePoint.x() == targetPoint.x() ||
            sourcePoint.y() == targetPoint.y()) {
            _drawShape.lineTo(targetPoint);
        } else {
            QPointF centerPoint = QPointF(
                (sourcePoint.x() + targetPoint.x()) / 2.0,
                (sourcePoint.y() + targetPoint.y()) / 2.0
            );
            _drawShape.cubicTo(
                centerPoint.x(),
                sourcePoint.y(),
                centerPoint.x(),
                targetPoint.y(),
                targetPoint.x(),
                targetPoint.y()
            );
        }
    }
}
