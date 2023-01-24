#include <QColor>
#include <QRectF>

#include "qnodeeditor_tree_model.hpp"

#include "qnodeeditor/qnodeeditor.hpp"
#include "qnodeeditor/qnodeeditor_connection.hpp"
#include "qnodeeditor/qnodeeditor_node.hpp"
#include "qnodeeditor/qnodeeditor_port.hpp"
#include "qnodeeditor/qnodeeditor_tree.hpp"

QNodeEditorTreeModel::QNodeEditorTreeModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

QNodeEditorTreeModel::~QNodeEditorTreeModel() { }

void QNodeEditorTreeModel::setTree(QNodeEditorTree* tree) { _tree = tree; }

QNodeEditorTree* QNodeEditorTreeModel::tree() const { return _tree; }

QNodeEditorNode* QNodeEditorTreeModel::addNode()
{
    beginInsertRows({}, rowCount(), rowCount());

    QNodeEditorNode* node = _tree->addNode();

    emit nodeAdded(index(node->_id, 0));

    endInsertRows();
    return node;
}

QNodeEditorConnection* QNodeEditorTreeModel::addConnection(
    uint64_t fromNodeId, uint64_t fromPort, uint64_t toNodeId, uint64_t toPort
)
{
    QNodeEditorConnection* connection =
        _tree->addConnection(fromNodeId, fromPort, toNodeId, toPort);
    emit connectionAdded(connection);
    return connection;
}

QModelIndex QNodeEditorTreeModel::index(
    int row, int column, const QModelIndex& parent
) const
{
    return createIndex(row, column, row);
}

int QNodeEditorTreeModel::rowCount(const QModelIndex& parent) const
{
    return _tree->nodesCount();
}

int QNodeEditorTreeModel::columnCount(const QModelIndex& parent) const
{
    return 3;
}

QVariant QNodeEditorTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= rowCount())
        return {};

    switch (role) {
        case Qt::DisplayRole: {
            switch (index.column()) {
                case 0: return tr("Node %0").arg(index.internalId());
                case 1:
                    return index.data(Inputs)
                        .value<QList<QNodeEditorPort*>>()
                        .size();
                case 2:
                    return index.data(Outputs)
                        .value<QList<QNodeEditorPort*>>()
                        .size();
            }
        }
        case NodeId: return index.row();
        case Connections: {
            QNodeEditorNode* node = _tree->node(index.internalId());
            return QVariant::fromValue<QList<QNodeEditorConnection*>>(
                node->_outgoingConnections
            );
        }
        case Color: {
            return QColor { 164, 45, 63, 255 };
        }
        case Inputs: {
            return QVariant::fromValue<QList<QNodeEditorPort*>>(
                _tree->node(index.internalId())->_inputPorts
            );
        }
        case Outputs: {
            return QVariant::fromValue<QList<QNodeEditorPort*>>(
                _tree->node(index.internalId())->_outputPorts
            );
        }
    }
    return {};
}

QVariant QNodeEditorTreeModel::headerData(
    int section, Qt::Orientation orientation, int role
) const
{
    switch (role) {
        case Qt::DisplayRole: {
            switch (section) {
                case 0: return "Name";
                case 1: return "Inputs";
                case 2: return "Outputs";
                default: return {};
            }
        }
        default: return {};
    }
}

uint64_t QNodeEditorTreeModel::idCounter = 0;
