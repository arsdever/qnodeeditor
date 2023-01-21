#pragma once

#include <QGraphicsObject>

class QNodeEditorPort;

class QNodeEditorPortGraphicsObject : public QGraphicsObject
{
public:
    explicit QNodeEditorPortGraphicsObject(
        std::shared_ptr<QNodeEditorPort> port, QGraphicsItem* parent = nullptr
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
    std::shared_ptr<QNodeEditorPort> _port;
};
