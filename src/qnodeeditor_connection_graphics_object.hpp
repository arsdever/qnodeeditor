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

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
#pragma endregion

private:
    QPointF sourcePosition() const;
    QPointF targetPosition() const;

private:
    QNodeEditor& _editor;
    QNodeEditorConnection* _connection;
    QStyle::State _state;
};
