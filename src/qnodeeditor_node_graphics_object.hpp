#pragma once

#include <QGraphicsObject>
#include <QModelIndex>

class QNodeEditorNodeGraphicsObject : public QGraphicsObject
{
public:
    explicit QNodeEditorNodeGraphicsObject(
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
