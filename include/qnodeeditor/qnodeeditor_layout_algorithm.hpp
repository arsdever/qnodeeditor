#pragma once

class QNodeEditor;
class QNodeEditorTree;

class QNodeEditorLayoutAlgorithm
{
public:
    explicit QNodeEditorLayoutAlgorithm(QNodeEditor& editor);
    virtual ~QNodeEditorLayoutAlgorithm();

    virtual void apply() = 0;

protected:
    QNodeEditorTree* getTree() const;

protected:
    QNodeEditor& _editor;
};
