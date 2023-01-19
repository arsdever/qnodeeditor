#pragma once

#include <QAbstractGraphicsShapeItem>
#include <QModelIndex>

class QNodeEditorNodeGraphicsItem : public QAbstractGraphicsShapeItem
{
public:
    explicit QNodeEditorNodeGraphicsItem(
        QModelIndex index, QGraphicsItem* parent = nullptr
    );

#pragma region QAbstractGraphicsShapeItem
    QRectF boundingRect() const override;
    void paint(
        QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget = nullptr
    ) override;
#pragma endregion

private:
	QModelIndex _index;
};
