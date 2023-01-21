#pragma once

#include <QGraphicsObject>
#include <QModelIndex>
#include <QStyle>

class QNodeEditorNodeGraphicsObject : public QGraphicsObject
{
public:
    explicit QNodeEditorNodeGraphicsObject(
        QModelIndex index, QGraphicsItem* parent = nullptr
    );

#pragma region QGraphicsObject
	public:
    QRectF boundingRect() const override;
    void paint(
        QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget = nullptr
    ) override;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
#pragma endregion

private:
    QModelIndex _index;
    QStyle::State _state;
};
