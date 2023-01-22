#pragma once

#include "qnodeeditor/qnodeeditor_layout_algorithm.hpp"

class QNodeEditorFlowLayoutAlgorithm : public QNodeEditorLayoutAlgorithm
{
public:
    explicit QNodeEditorFlowLayoutAlgorithm(QNodeEditor& editor);
    ~QNodeEditorFlowLayoutAlgorithm() override;

    void apply() override;

private:
    void calculateRanks();

private:
    std::unordered_map<uint64_t, int> _ranks;
};
