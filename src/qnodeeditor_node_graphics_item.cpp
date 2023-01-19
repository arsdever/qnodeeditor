#include <QFontMetrics>
#include <QPainter>

#include "qnodeeditor_node_graphics_item.hpp"

#include "qnodeeditor_tree_model.hpp"

namespace
{
// TODO instead have a style option
static constexpr int PORT_SIZE = 6;
static constexpr int PORT_SPACING = 15;
static constexpr int NODE_PADDING = 5;
} // namespace

QNodeEditorNodeGraphicsItem::QNodeEditorNodeGraphicsItem(
    QModelIndex index, QGraphicsItem* parent
)
    : QAbstractGraphicsShapeItem(parent)
    , _index(index)
{
}

QRectF QNodeEditorNodeGraphicsItem::boundingRect() const
{
    std::size_t maxPortCount = std::max(
        _index.data(QNodeEditorTreeModel::NodeDataRole::Inputs)
            .value<QList<QNodeEditorNode::Port>>()
            .size(),
        _index.data(QNodeEditorTreeModel::NodeDataRole::Outputs)
            .value<QList<QNodeEditorNode::Port>>()
            .size()
    );

    std::size_t height =
        2 * NODE_PADDING + QPainter().fontMetrics().height() +
        std::max(std::size_t(0), (maxPortCount - 1)) * PORT_SPACING;

    return QRectF(
        // TODO fix me
        _index.row() * 150,
        0,
        // TODO fetch from name
        100,
        height
    );
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
