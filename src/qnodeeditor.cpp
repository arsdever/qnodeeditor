#include <QGraphicsScene>
#include <QGraphicsView>
#include <QOpenGLWidget>

#include "qnodeeditor/qnodeeditor.hpp"

namespace
{
static constexpr int GRID_COUNT = 10000;
} // namespace

QNodeEditor::QNodeEditor(QWidget* parent)
    : QWidget(parent)
{
    m_view = new QGraphicsView(this);
    m_scene = new QGraphicsScene(this);
    m_view->setScene(m_scene);
    m_view->setViewport(new QOpenGLWidget(this));

    addGrid();

    m_scene->setSceneRect({});
}

void QNodeEditor::addGrid()
{
    for (int i = 0; i < GRID_COUNT; ++i) {
        if (i == GRID_COUNT / 2)
            continue;

        if (i % 10 == 0)
            continue;

        QPen pen = QPen(palette().color(QPalette::Background).lighter(110));
        m_scene->addLine(
            (i - GRID_COUNT / 2) * 10,
            -100000,
            (i - GRID_COUNT / 2) * 10,
            100000,
            pen
        );
        m_scene->addLine(
            -100000,
            (i - GRID_COUNT / 2) * 10,
            100000,
            (i - GRID_COUNT / 2) * 10,
            pen
        );
    }

    for (int i = 0; i < GRID_COUNT; i += 10) {
        if (i == GRID_COUNT / 2)
            continue;

        QPen pen = QPen(palette().color(QPalette::Background).lighter(200));
        m_scene->addLine(
            (i - GRID_COUNT / 2) * 10,
            -100000,
            (i - GRID_COUNT / 2) * 10,
            100000,
            pen
        );
        m_scene->addLine(
            -100000,
            (i - GRID_COUNT / 2) * 10,
            100000,
            (i - GRID_COUNT / 2) * 10,
            pen
        );
    }

    QPen pen = QPen(palette().color(QPalette::Background).lighter(200), 5);
    m_scene->addLine(0, -100000, 0, 100000, pen);
    m_scene->addLine(-100000, 0, 100000, 0, pen);
}
