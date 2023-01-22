#include <QList>
#include <QMetaType>
#include <functional>
#include <queue>
#include <string_view>

#include "qnodeeditor/qnodeeditor_flow_layout_algorithm.hpp"

#include "qnodeeditor/qnodeeditor_connection.hpp"
#include "qnodeeditor/qnodeeditor_node.hpp"
#include "qnodeeditor/qnodeeditor_port.hpp"
#include "qnodeeditor/qnodeeditor_tree.hpp"

QNodeEditorFlowLayoutAlgorithm::QNodeEditorFlowLayoutAlgorithm(
    QNodeEditor& editor
)
    : QNodeEditorLayoutAlgorithm(editor)
{
}

QNodeEditorFlowLayoutAlgorithm::~QNodeEditorFlowLayoutAlgorithm() = default;

void QNodeEditorFlowLayoutAlgorithm::apply() { calculateRanks(); }

void QNodeEditorFlowLayoutAlgorithm::calculateRanks()
{
    QNodeEditorTree* tree = getTree();
    tree->forEachNode([ tree, this ](QNodeEditorNode* node) -> bool {
        if (node->_incomingConnections.empty()) {
            // BFS to rank all nodes
            _ranks[ node->_id ] = 0;
            node->_rank = 0;

            std::queue<QNodeEditorNode*> queue;
            for (auto& connection : node->_outgoingConnections)
                queue.push(connection->_to->_node);

            while (!queue.empty()) {
                auto& node = queue.front();
                queue.pop();

                int maxRank = 0;

                for (auto& connection : node->_incomingConnections) {
                    auto& rank = _ranks[ connection->_from->_node->_id ];
                    if (rank > maxRank)
                        maxRank = rank;
                }
                _ranks[ node->_id ] = maxRank + 1;
                node->_rank = maxRank + 1;

                for (auto& connection : node->_outgoingConnections)
                    queue.push(connection->_to->_node);
            }

            return _ranks.size() == tree->nodesCount();
        }

        return true;
    });
}
