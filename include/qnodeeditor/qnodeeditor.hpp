#pragma once

#include <QModelIndex>
#include <QWidget>
#include <unordered_map>

class QGraphicsItem;
class QGraphicsScene;
class QGraphicsView;
class QNodeEditorTree;
class QNodeEditorTreeModel;
class QNodeEditorConnection;
class QNodeEditorPort;

enum class PortType { In, Out };

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

    void addConnectionGraphics(QNodeEditorConnection* connection);
    void removeConnection(QNodeEditorConnection* connection);

    QPointF getPortPosition(QNodeEditorPort* port) const;

private:
    friend class QNodeEditorConnectionGraphicsObject;

private:
    QGraphicsView* _view;
    QGraphicsScene* _scene;
    QNodeEditorTree* _tree;
    std::unordered_map<uint64_t, QGraphicsItem*>
        _model_index_graphics_item_mapping;
};
