#pragma once

#include <QWidget>

class QGraphicsView;
class QGraphicsScene;

class QNodeEditor : public QWidget
{
public:
    explicit QNodeEditor(QWidget* parent = nullptr);

private:
    void addGrid();

private:
    QGraphicsView* m_view;
    QGraphicsScene* m_scene;
};
