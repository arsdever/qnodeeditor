#include <QFontMetrics>
#include <QLinearGradient>
#include <QPainter>

#include "qnodeeditor_node_graphics_item.hpp"

#include "qnodeeditor_tree_model.hpp"

namespace
{
// TODO instead have a style option
static constexpr float PORT_SIZE = 10;
static constexpr float PORT_SPACING = 20;
static constexpr float NODE_PADDING = 10;
} // namespace

QNodeEditorNodeGraphicsItem::QNodeEditorNodeGraphicsItem(
    QModelIndex index, QGraphicsItem* parent
)
    : QGraphicsObject(parent)
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
        3 * NODE_PADDING + QPainter().fontMetrics().height() +
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
    painter->fillRect(titleRect, QColor(0, 0, 0, 64));
    auto inputPorts = _index.data(QNodeEditorTreeModel::NodeDataRole::Inputs)
                          .value<QList<QNodeEditorNode::Port>>();
    auto outputPorts = _index.data(QNodeEditorTreeModel::NodeDataRole::Outputs)
                           .value<QList<QNodeEditorNode::Port>>();
    painter->save();
    painter->translate(boundingRect().topLeft());
    painter->translate(
        0, PORT_SPACING / 2 + NODE_PADDING + painter->fontMetrics().height()
    );
    painter->save();
    std::for_each(
        inputPorts.begin(),
        inputPorts.end(),
        [ painter ](auto& port) {
        QPen pen {
            QColor {23, 85, 12},
             3
        };
        QBrush brush {
            QColor {45, 213, 54}
        };
        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawEllipse(
            -PORT_SIZE / 2, -PORT_SIZE / 2, PORT_SIZE, PORT_SIZE
        );
        painter->translate(0, PORT_SPACING);
        });
    painter->restore();
    painter->translate(boundingRect().width(), 0);
    std::for_each(
        outputPorts.begin(),
        outputPorts.end(),
        [ painter ](auto& port) {
        QPen pen {
            QColor {23, 85, 12},
             3
        };
        QBrush brush {
            QColor {45, 213, 54}
        };
        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawEllipse(
            -PORT_SIZE / 2, -PORT_SIZE / 2, PORT_SIZE, PORT_SIZE
        );
        painter->translate(0, PORT_SPACING);
        });
    painter->restore();
}
