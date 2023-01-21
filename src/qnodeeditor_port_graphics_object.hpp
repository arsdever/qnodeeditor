#pragma once

#include <QGraphicsObject>
#include <QStyle>

class QNodeEditorPort;

class QNodeEditorPortGraphicsObject : public QGraphicsObject
{
public:
    explicit QNodeEditorPortGraphicsObject(
        QNodeEditorPort* port, QGraphicsItem* parent = nullptr
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
    std::shared_ptr<QNodeEditorPort> _port;
    QStyle::State _state;
};
