#pragma once

#include <QGraphicsObject>

class QNodeEditor;
class QNodeEditorConnection;

class QNodeEditorConnectionGraphicsObject : public QGraphicsObject
{
public:
    explicit QNodeEditorConnectionGraphicsObject(
		QNodeEditor& editor,
        QNodeEditorConnection* connection, QGraphicsItem* parent = nullptr
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
	QPointF sourcePosition() const;
	QPointF targetPosition() const;

private:
    QNodeEditor& _editor;
    QNodeEditorConnection* _connection;
};
