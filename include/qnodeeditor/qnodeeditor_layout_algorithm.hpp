#pragma once

class QNodeEditor;
class QNodeEditorTree;
class QNodeEditorNodeGraphicsObject;

class QNodeEditorLayoutAlgorithm
{
public:
    explicit QNodeEditorLayoutAlgorithm(QNodeEditor& editor);
    virtual ~QNodeEditorLayoutAlgorithm();

    virtual void apply() = 0;

protected:
    QNodeEditorTree* getTree() const;
    QNodeEditorNodeGraphicsObject* getGraphics(uint64_t id) const;

protected:
    QNodeEditor& _editor;
};
