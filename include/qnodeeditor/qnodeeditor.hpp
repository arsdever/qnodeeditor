#pragma once

#include <QModelIndex>
#include <QWidget>
#include <unordered_map>

class QGraphicsItem;
class QGraphicsScene;
class QGraphicsView;
class QNodeEditorTree;
class QNodeEditorTreeModel;

class QNodeEditor : public QWidget
{
public:
    explicit QNodeEditor(QWidget* parent = nullptr);

    void setTree(QNodeEditorTree* tree);

private:
    void addGrid();
    void setupModelConnections(QNodeEditorTreeModel* model);

    void addNodeGraphics(QModelIndex index);
    void removeNodeGraphics(QModelIndex index);
    void removeAllNodeGraphics();

    void addConnection(uint64_t from, uint64_t to);
    void removeConnection(uint64_t from, uint64_t to);

private:
    QGraphicsView* _view;
    QGraphicsScene* _scene;
    QNodeEditorTree* _tree;
    std::unordered_map<uint64_t, QGraphicsItem*>
        _model_index_graphics_item_mapping;
};
