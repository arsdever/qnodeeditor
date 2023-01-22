#include <inttypes.h>

#include "qnodeeditor/qnodeeditor_layout_algorithm.hpp"

#include "qnodeeditor/qnodeeditor.hpp"
#include "qnodeeditor_node_graphics_object.hpp"

QNodeEditorLayoutAlgorithm::QNodeEditorLayoutAlgorithm(QNodeEditor& editor)
    : _editor(editor)
{
}

QNodeEditorLayoutAlgorithm::~QNodeEditorLayoutAlgorithm() = default;

QNodeEditorTree* QNodeEditorLayoutAlgorithm::getTree() const
{
    return _editor._tree;
}

QNodeEditorNodeGraphicsObject* QNodeEditorLayoutAlgorithm::getGraphics(
    uint64_t id
) const
{
    return dynamic_cast<QNodeEditorNodeGraphicsObject*>(
        _editor._model_index_graphics_item_mapping[ id ]
    );
}
