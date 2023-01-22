#include <QList>
#include <QMetaType>
#include <functional>
#include <queue>
#include <string_view>

#include "qnodeeditor/qnodeeditor_flow_layout_algorithm.hpp"

#include "qnodeeditor/qnodeeditor.hpp"
#include "qnodeeditor/qnodeeditor_connection.hpp"
#include "qnodeeditor/qnodeeditor_node.hpp"
#include "qnodeeditor/qnodeeditor_port.hpp"
#include "qnodeeditor/qnodeeditor_tree.hpp"
#include "qnodeeditor_node_graphics_object.hpp"

QNodeEditorFlowLayoutAlgorithm::QNodeEditorFlowLayoutAlgorithm(
    QNodeEditor& editor
)
    : QNodeEditorLayoutAlgorithm(editor)
{
}

QNodeEditorFlowLayoutAlgorithm::~QNodeEditorFlowLayoutAlgorithm() = default;

void QNodeEditorFlowLayoutAlgorithm::apply()
{
    calculateRanks();
    auto paths = calculatePaths();
    std::vector<std::vector<uint64_t>> layout(
        _ranks.size(), std::vector<uint64_t> {}
    );

    for (auto& [ id, rank ] : _ranks)
        layout[ rank ].push_back(id);

    for (auto& layer : layout) {
        std::sort(
            layer.begin(),
            layer.end(),
            [ &paths ](uint64_t a, uint64_t b) {
            return paths[ a ].size() > paths[ b ].size();
            });
    }

    for (auto& [ id, rank ] : _ranks) {
        auto* graphics = getGraphics(id);
        std::size_t index = std::distance(
            layout[ rank ].begin(),
            std::find(layout[ rank ].begin(), layout[ rank ].end(), id)
        );
        graphics->setPos(rank * 200, index * 100);
    }
}

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

std::unordered_map<uint64_t, std::vector<QNodeEditorNode*>>
    QNodeEditorFlowLayoutAlgorithm::calculatePaths()
{
    std::unordered_map<uint64_t, std::vector<QNodeEditorNode*>> paths;
    QNodeEditorTree* tree = getTree();

    tree->forEachNode(
        [ this, tree, &paths ](QNodeEditorNode* targetNode) -> bool {
            if (targetNode->_incomingConnections.empty()) {
                // DFS to find all paths
                std::vector<QNodeEditorNode*> path;

                std::function<bool(QNodeEditorNode*)> dfs =
                    [ this, tree, targetNode, &paths, &path, &dfs ](
                        QNodeEditorNode* node
                    ) -> bool {
                    path.push_back(node);

                    if (node == targetNode) {
                        paths[ node->_id ] = path;
                        return true;
                    }

                    for (auto& connection : node->_outgoingConnections) {
                        if (dfs(connection->_to->_node))
                            return true;
                        path.pop_back();
                    }

                    return false;
                };

                dfs(targetNode);
            }

            return true;
        }
    );

    return paths;
}
