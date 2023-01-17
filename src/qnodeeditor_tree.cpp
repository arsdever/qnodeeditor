#include <QAbstractListModel>

#include "qnodeeditor/qnodeeditor_tree.hpp"

#include "qnodeeditor_tree_model.hpp"

QNodeEditorTree::QNodeEditorTree()
    : _model(new QNodeEditorTreeModel())
{
}

QNodeEditorTree::~QNodeEditorTree() { delete _model; }

uint64_t QNodeEditorTree::addNode()
{
    return qobject_cast<QNodeEditorTreeModel*>(_model)->addNode();
}

void QNodeEditorTree::addConnection(uint64_t from, uint64_t to)
{
    qobject_cast<QNodeEditorTreeModel*>(_model)->addConnection(from, to);
}

QAbstractItemModel* QNodeEditorTree::model() const { return _model; }
