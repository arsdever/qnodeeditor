#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QOpenGLWidget>

#include "qnodeeditor/qnodeeditor.hpp"

#include "qnodeeditor/qnodeeditor_tree.hpp"
#include "qnodeeditor_node_graphics_object.hpp"
#include "qnodeeditor_tree_model.hpp"

namespace
{
static constexpr int GRID_COUNT = 10000;
} // namespace

QNodeEditor::QNodeEditor(QWidget* parent)
    : QWidget(parent)
{
    _view = new QGraphicsView(this);
    _scene = new QGraphicsScene(this);
    _view->setScene(_scene);
    _view->setViewport(new QOpenGLWidget(this));

    addGrid();

    _scene->setSceneRect({});
}

void QNodeEditor::setTree(QNodeEditorTree* tree)
{
    _tree = tree;
    setupModelConnections(qobject_cast<QNodeEditorTreeModel*>(tree->model()));
    for (int i = 0; i < tree->model()->rowCount(); ++i) {
        auto index = tree->model()->index(i, 0);
        QGraphicsItem* item = new QNodeEditorNodeGraphicsObject(index);
        item->setPos( // TODO fix me
            index.row() * 150,
            0
        );
        _scene->addItem(item);
        _model_index_graphics_item_mapping.emplace(
            reinterpret_cast<uint64_t>(index.internalId()), item
        );
    }
}

void QNodeEditor::addGrid()
{
    for (int i = 0; i < GRID_COUNT; ++i) {
        if (i == GRID_COUNT / 2)
            continue;

        if (i % 10 == 0)
            continue;

        QPen pen = QPen(palette().color(QPalette::Window).lighter(110));
        _scene->addLine(
            (i - GRID_COUNT / 2) * 10,
            -100000,
            (i - GRID_COUNT / 2) * 10,
            100000,
            pen
        );
        _scene->addLine(
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

        QPen pen = QPen(palette().color(QPalette::Window).lighter(200));
        _scene->addLine(
            (i - GRID_COUNT / 2) * 10,
            -100000,
            (i - GRID_COUNT / 2) * 10,
            100000,
            pen
        );
        _scene->addLine(
            -100000,
            (i - GRID_COUNT / 2) * 10,
            100000,
            (i - GRID_COUNT / 2) * 10,
            pen
        );
    }

    QPen pen = QPen(palette().color(QPalette::Window).lighter(200), 5);
    _scene->addLine(0, -100000, 0, 100000, pen);
    _scene->addLine(-100000, 0, 100000, 0, pen);
}

void QNodeEditor::setupModelConnections(QNodeEditorTreeModel* model)
{
    connect(
        model,
        QOverload<const QModelIndex&, const QModelIndex&, const QVector<int>&>::
            of(&QAbstractItemModel::dataChanged),
        this,
        [ this ](
            const QModelIndex& topLeft,
            const QModelIndex& bottomRight,
            const QVector<int>& roles
        ) {
        // TBD
        });

    connect(
        model,
        &QAbstractItemModel::rowsInserted,
        this,
        [ model, this ](const QModelIndex& parent, int first, int last) {
        for (int i = first; i <= last; ++i)
            addNodeGraphics(model->index(i, 0, parent));
        });

    connect(
        model,
        &QAbstractItemModel::rowsAboutToBeRemoved,
        this,
        [ model, this ](const QModelIndex& parent, int first, int last) {
        for (int i = first; i <= last; ++i)
            removeNodeGraphics(model->index(i, 0, parent));
        });

    connect(model, &QAbstractItemModel::modelAboutToBeReset, this, [ this ] {
        removeAllNodeGraphics();
    });

    connect(model, &QAbstractItemModel::modelReset, this, [ this ]() {
        for (int i = 0; i < _tree->model()->rowCount(); ++i) {
            auto index = _tree->model()->index(i, 0);
            addNodeGraphics(index);
        }
    });

    connect(
        model,
        &QNodeEditorTreeModel::connectionAdded,
        this,
        [ this ](QModelIndex from, QModelIndex to) {}
    );
}

void QNodeEditor::addNodeGraphics(QModelIndex index)
{
    QGraphicsItem* item = new QNodeEditorNodeGraphicsObject(index);
    item->setPos( // TODO fix me
        index.row() * 150,
        0
    );
    _scene->addItem(item);
    _model_index_graphics_item_mapping.emplace(
        reinterpret_cast<uint64_t>(index.internalId()), item
    );
}

void QNodeEditor::removeNodeGraphics(QModelIndex index)
{
    auto it = _model_index_graphics_item_mapping.find(
        reinterpret_cast<uint64_t>(index.internalId())
    );
    if (it != _model_index_graphics_item_mapping.end()) {
        _scene->removeItem(it->second);
        delete it->second;
        _model_index_graphics_item_mapping.erase(it);
    }
}

void QNodeEditor::removeAllNodeGraphics()
{
    for (auto& [ key, value ] : _model_index_graphics_item_mapping) {
        _scene->removeItem(value);
        delete value;
    }
    _model_index_graphics_item_mapping.clear();
}
