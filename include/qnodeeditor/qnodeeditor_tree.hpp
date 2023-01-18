#pragma once

#include <QObject>

class QAbstractItemModel;

class QNodeEditorTree : public QObject
{
public:
    explicit QNodeEditorTree(QObject* parent = nullptr);
    ~QNodeEditorTree();

    uint64_t addNode();
    void addConnection(uint64_t from, uint64_t to);

    QAbstractItemModel* model() const;

private:
    QAbstractItemModel* _model;
};
