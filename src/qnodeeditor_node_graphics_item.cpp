#include <QPainter>

#include "qnodeeditor_node_graphics_item.hpp"

#include "qnodeeditor_tree_model.hpp"

QNodeEditorNodeGraphicsItem::QNodeEditorNodeGraphicsItem(
    QModelIndex index, QGraphicsItem* parent
)
    : QAbstractGraphicsShapeItem(parent)
    , _index(index)
{
}

QRectF QNodeEditorNodeGraphicsItem::boundingRect() const
{
    return _index.data(QNodeEditorTreeModel::NodeDataRole::Rect)
        .value<QRectF>();
}

void QNodeEditorNodeGraphicsItem::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
)
{
    painter->fillRect(
        boundingRect(),
        _index.data(QNodeEditorTreeModel::NodeDataRole::Color).value<QColor>()
    );
}
