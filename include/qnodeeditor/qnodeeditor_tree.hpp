#pragma once

class QAbstractItemModel;

class QNodeEditorTree
{
public:
    explicit QNodeEditorTree();
    ~QNodeEditorTree();

    uint64_t addNode();
    void addConnection(uint64_t from, uint64_t to);

    QAbstractItemModel* model() const;

private:
    QAbstractItemModel* _model;
};
