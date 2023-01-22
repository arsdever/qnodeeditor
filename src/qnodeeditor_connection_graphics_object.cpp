#include <QPainter>
#include <QPainterPath>

#include "qnodeeditor_connection_graphics_object.hpp"

#include "qnodeeditor/qnodeeditor.hpp"
#include "qnodeeditor/qnodeeditor_connection.hpp"
#include "qnodeeditor/qnodeeditor_port.hpp"

namespace
{
// check the shape when changing the ARC_DIAMETER
static constexpr double ARC_DIAMETER = 20;
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
        if (sourcePoint.x() == targetPoint.x() ||
            sourcePoint.y() == targetPoint.y()) {
            _shape.addRect(QRectF(sourcePoint, targetPoint)
                               .normalized()
                               .adjusted(
                                   SHAPE_CLEARANCE,
                                   -SHAPE_CLEARANCE,
                                   -SHAPE_CLEARANCE,
                                   SHAPE_CLEARANCE
                               ));
        } else {
            double diameter = std::min(
                ARC_DIAMETER,
                std::min(
                    boundingRect().width() - SHAPE_CLEARANCE,
                    boundingRect().height() - SHAPE_CLEARANCE
                )
            );
            QPointF centerPoint = QPointF(
                (sourcePoint.x() + targetPoint.x()) / 2.0,
                (sourcePoint.y() + targetPoint.y()) / 2.0
            );
            QRegion region;
            region = region.united(
                QRectF(sourcePoint, QPointF(centerPoint.x(), sourcePoint.y()))
                    .normalized()
                    .adjusted(
                        SHAPE_CLEARANCE,
                        -SHAPE_CLEARANCE,
                        -SHAPE_CLEARANCE,
                        SHAPE_CLEARANCE
                    )
                    .toRect()
            );
            region =
                region.united(QRectF(
                                  QPointF(centerPoint.x(), sourcePoint.y()),
                                  QPointF(centerPoint.x(), targetPoint.y())
                )
                                  .normalized()
                                  .adjusted(
                                      -SHAPE_CLEARANCE,
                                      -SHAPE_CLEARANCE,
                                      SHAPE_CLEARANCE,
                                      SHAPE_CLEARANCE
                                  )
                                  .toRect());
            region = region.united(
                QRectF(targetPoint, QPointF(centerPoint.x(), targetPoint.y()))
                    .normalized()
                    .adjusted(
                        -SHAPE_CLEARANCE,
                        -SHAPE_CLEARANCE,
                        -SHAPE_CLEARANCE,
                        SHAPE_CLEARANCE
                    )
                    .toRect()
            );
            _shape.addRegion(region);
        }
    }
}

void QNodeEditorConnectionGraphicsObject::recalculateDrawingShape(
    QPointF sourcePoint, QPointF targetPoint
) const
{
    _drawShape.clear();
    _drawShape.moveTo(sourcePoint);
    if (sourcePoint.x() == targetPoint.x() ||
        sourcePoint.y() == targetPoint.y()) {
        _drawShape.lineTo(targetPoint);
    } else {
        // draw horizontal line from source to the middle
        // continue with arc to a vertical line
        // continue with arc to a horizontal line untli the target
        QPointF centerPoint = QPointF(
            (sourcePoint.x() + targetPoint.x()) / 2.0,
            (sourcePoint.y() + targetPoint.y()) / 2.0
        );

        double diameter = std::min(
            ARC_DIAMETER,
            std::min(
                boundingRect().width() - SHAPE_CLEARANCE,
                boundingRect().height() - SHAPE_CLEARANCE
            )
        );
        _drawShape.lineTo(centerPoint.x() - diameter / 2.0, sourcePoint.y());
        if (sourcePoint.y() > targetPoint.y()) {
            _drawShape.arcTo(
                QRectF { centerPoint.x() - diameter,
                         sourcePoint.y() - diameter,
                         diameter,
                         diameter },
                270,
                90
            );
            _drawShape.lineTo(
                centerPoint.x(), targetPoint.y() + diameter / 2.0
            );
            _drawShape.arcTo(
                QRectF { centerPoint.x(), targetPoint.y(), diameter, diameter },
                180,
                -90
            );
        } else {
            _drawShape.arcTo(
                QRectF { centerPoint.x() - diameter,
                         sourcePoint.y(),
                         diameter,
                         diameter },
                90,
                -90
            );
            _drawShape.lineTo(
                centerPoint.x(), targetPoint.y() - diameter / 2.0
            );
            _drawShape.arcTo(
                QRectF { centerPoint.x(),
                         targetPoint.y() - diameter,
                         diameter,
                         diameter },
                180,
                90
            );
        }
        _drawShape.lineTo(targetPoint);
    }
}
