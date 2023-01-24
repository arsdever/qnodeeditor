#pragma once

#include <QModelIndex>
#include <QWidget>
#include <unordered_map>

class QAbstractItemModel;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsView;
class QNodeEditorConnection;
class QNodeEditorPort;
class QNodeEditorTree;
class QNodeEditorTreeModel;

enum class PortType { In, Out };

class QNodeEditor : public QWidget
{
public:
    explicit QNodeEditor(QWidget* parent = nullptr);

    void setTree(QNodeEditorTree* tree);
    QAbstractItemModel* model() const;

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
    friend class QNodeEditorLayoutAlgorithm;
    friend class QNodeEditorConnectionGraphicsObject;

private:
    QGraphicsView* _view = nullptr;
    QGraphicsScene* _scene = nullptr;
    QNodeEditorTree* _tree = nullptr;
    QNodeEditorTreeModel* _model = nullptr;
    std::unordered_map<uint64_t, QGraphicsItem*>
        _model_index_graphics_item_mapping;
};
