#include "qnodeeditor/qnodeeditor_layout_algorithm.hpp"

#include "qnodeeditor/qnodeeditor.hpp"

QNodeEditorLayoutAlgorithm::QNodeEditorLayoutAlgorithm(QNodeEditor& editor)
    : _editor(editor)
{
}

QNodeEditorLayoutAlgorithm::~QNodeEditorLayoutAlgorithm() = default;

QNodeEditorTree* QNodeEditorLayoutAlgorithm::getTree() const
{
    return _editor._tree;
}
