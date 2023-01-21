#include <QPainter>

#include "qnodeeditor_port_graphics_object.hpp"

#include "qnodeeditor/qnodeeditor_port.hpp"

QNodeEditorPortGraphicsObject::QNodeEditorPortGraphicsObject(
    std::shared_ptr<QNodeEditorPort> port, QGraphicsItem* parent
)
    : QGraphicsObject(parent)
    , _port(port)
    , _state(QStyle::State_None)
{
    setAcceptHoverEvents(true);
}

QRectF QNodeEditorPortGraphicsObject::boundingRect() const
{
    return QRectF(-8, -8, 16, 16);
}

void QNodeEditorPortGraphicsObject::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->save();
    painter->setPen(QPen(Qt::black, _state & QStyle::State_MouseOver ? 3 : 2));
    painter->setBrush(Qt::green);
    painter->drawEllipse(
        _state & QStyle::State_MouseOver ? boundingRect()
                                         : boundingRect().adjusted(2, 2, -2, -2)
    );
    painter->restore();
}

void QNodeEditorPortGraphicsObject::hoverEnterEvent(
    QGraphicsSceneHoverEvent* event
)
{
    _state |= QStyle::State_MouseOver;
    update();
}

void QNodeEditorPortGraphicsObject::hoverLeaveEvent(
    QGraphicsSceneHoverEvent* event
)
{
    _state &= ~QStyle::State_MouseOver;
    update();
}
