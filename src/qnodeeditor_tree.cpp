#include "qnodeeditor/qnodeeditor_tree.hpp"

#include "qnodeeditor_tree_model.hpp"

QNodeEditorTree::QNodeEditorTree(QObject* parent)
    : QObject(parent)
    , _model(new QNodeEditorTreeModel())
{
}

QNodeEditorTree::~QNodeEditorTree() { delete _model; }

uint64_t QNodeEditorTree::addNode()
{
    std::size_t id = _model->addNode();
    return id;
}

void QNodeEditorTree::addConnection(
    uint64_t fromNodeId, uint64_t fromPort, uint64_t toNodeId, uint64_t toPort
)
{
    _model->addConnection(fromNodeId, fromPort, toNodeId, toPort);
}

QAbstractItemModel* QNodeEditorTree::model() const { return _model; }
