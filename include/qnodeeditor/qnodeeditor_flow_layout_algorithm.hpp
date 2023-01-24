#pragma once

#include "qnodeeditor/qnodeeditor_layout_algorithm.hpp"

class QNodeEditor;
class QNodeEditorNode;

class QNodeEditorFlowLayoutAlgorithm : public QNodeEditorLayoutAlgorithm
{
public:
    explicit QNodeEditorFlowLayoutAlgorithm(QNodeEditor& editor);
    ~QNodeEditorFlowLayoutAlgorithm() override;

    void apply() override;

private:
    void calculateRanks();
    std::unordered_map<uint64_t, std::vector<QNodeEditorNode*>> calculatePaths(
    );

private:
    std::unordered_map<uint64_t, int> _ranks;
};
