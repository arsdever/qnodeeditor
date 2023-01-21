#include <QPainter>

#include "qnodeeditor/qnodeeditor_port.hpp"
#include "qnodeeditor_port_graphics_object.hpp"

QNodeEditorPortGraphicsObject::QNodeEditorPortGraphicsObject(
    std::shared_ptr<QNodeEditorPort> port, QGraphicsItem* parent
)
    : QGraphicsObject(parent)
    , _port(port)
{
}

QRectF QNodeEditorPortGraphicsObject::boundingRect() const
{
    return QRectF(-6, -6, 12, 12);
}

void QNodeEditorPortGraphicsObject::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
)
{
    painter->save();
    painter->setPen(QPen(Qt::black, 3));
    painter->setBrush(Qt::green);
    painter->drawEllipse(boundingRect());
    painter->restore();
}
