#include <QDebug>
#include <QFontMetrics>
#include <QLinearGradient>
#include <QPainter>

#include "qnodeeditor_node_graphics_object.hpp"

#include "qnodeeditor_port_graphics_object.hpp"
#include "qnodeeditor_tree_model.hpp"

namespace
{
// TODO instead have a style option
static constexpr float PORT_SIZE = 10;
static constexpr float PORT_SPACING = 20;
static constexpr float NODE_PADDING = 10;
} // namespace

QNodeEditorNodeGraphicsObject::QNodeEditorNodeGraphicsObject(
    QModelIndex index, QGraphicsItem* parent
)
    : QGraphicsObject(parent)
    , _index(index)
{
    std::size_t portIndex = 0;
    for (auto& port : _index.data(QNodeEditorTreeModel::NodeDataRole::Inputs)
                          .value<QList<std::shared_ptr<QNodeEditorPort>>>()) {
        QGraphicsItem* item = new QNodeEditorPortGraphicsObject(port, this);
        item->setPos(
            0,
            (portIndex + .5) * PORT_SPACING + NODE_PADDING +
                QPainter().fontMetrics().height()
        );
        ++portIndex;
    }

    portIndex = 0;
    for (auto& port : _index.data(QNodeEditorTreeModel::NodeDataRole::Outputs)
                          .value<QList<std::shared_ptr<QNodeEditorPort>>>()) {
        QGraphicsItem* item = new QNodeEditorPortGraphicsObject(port, this);
        item->setPos(
            boundingRect().width(),
            (portIndex + .5) * PORT_SPACING + NODE_PADDING +
                QPainter().fontMetrics().height()
        );
        ++portIndex;
    }
}

QRectF QNodeEditorNodeGraphicsObject::boundingRect() const
{
    std::size_t maxPortCount = std::max(
        _index.data(QNodeEditorTreeModel::NodeDataRole::Inputs)
            .value<QList<std::shared_ptr<QNodeEditorPort>>>()
            .size(),
        _index.data(QNodeEditorTreeModel::NodeDataRole::Outputs)
            .value<QList<std::shared_ptr<QNodeEditorPort>>>()
            .size()
    );

    std::size_t height =
        3 * NODE_PADDING + QPainter().fontMetrics().height() +
        std::max(0, static_cast<int>(maxPortCount) - 1) * PORT_SPACING;

    return QRectF(
        0,
        0,
        // TODO fetch from name
        100,
        height
    );
}

void QNodeEditorNodeGraphicsObject::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
)
{
    painter->save();
    QPen pen { Qt::black, 2 };
    QLinearGradient gradient { boundingRect().topLeft(),
                               boundingRect().bottomLeft() };
    gradient.setColorAt(
        0,
        _index.data(QNodeEditorTreeModel::NodeDataRole::Color)
            .value<QColor>()
            .lighter(130)
    );
    gradient.setColorAt(
        1,
        _index.data(QNodeEditorTreeModel::NodeDataRole::Color)
            .value<QColor>()
            .darker(130)
    );
    QBrush brush { gradient };
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRoundedRect(boundingRect(), 5, 5);
    painter->restore();
    QRectF titleRect = { boundingRect().left() + NODE_PADDING,
                         boundingRect().top() + NODE_PADDING,
                         boundingRect().width() - NODE_PADDING * 2,
                         static_cast<double>(painter->fontMetrics().height()) };
    painter->drawText(
        titleRect,
        Qt::AlignHCenter | Qt::TextSingleLine,
        _index.data(Qt::DisplayRole).toString()
    );
}
