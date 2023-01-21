#pragma once

#include <QGraphicsObject>
#include <QModelIndex>

class QNodeEditorNodeGraphicsItem : public QGraphicsObject
{
public:
    explicit QNodeEditorNodeGraphicsItem(
        QModelIndex index, QGraphicsItem* parent = nullptr
    );

#pragma region QGraphicsObject
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
