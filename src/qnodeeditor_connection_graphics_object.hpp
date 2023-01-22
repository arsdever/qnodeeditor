#pragma once

#include <QGraphicsObject>
#include <QStyle>

class QNodeEditor;
class QNodeEditorConnection;

class QNodeEditorConnectionGraphicsObject : public QGraphicsObject
{
public:
    explicit QNodeEditorConnectionGraphicsObject(
        QNodeEditor& editor,
        QNodeEditorConnection* connection,
        QGraphicsItem* parent = nullptr
    );

#pragma region QGraphicsObject
    QRectF boundingRect() const override;
    void paint(
        QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget = nullptr
    ) override;
    QPainterPath shape() const override;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
#pragma endregion

private:
    QPointF sourcePosition() const;
    QPointF targetPosition() const;
	void recalculateShape(QPointF sourcePoint, QPointF targetPoint) const;
	void recalculateDrawingShape(QPointF sourcePoint, QPointF targetPoint) const;

private:
    QNodeEditor& _editor;
    QNodeEditorConnection* _connection;
    QStyle::State _state;
    mutable QPointF _cachedSourcePosition;
    mutable QPointF _cachedTargetPosition;
    mutable QPainterPath _shape;
    mutable QPainterPath _drawShape;
};
