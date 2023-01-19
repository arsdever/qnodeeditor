#include <QColor>
#include <QRectF>

#include "qnodeeditor_tree_model.hpp"

QNodeEditorTreeModel::QNodeEditorTreeModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

QNodeEditorTreeModel::~QNodeEditorTreeModel() { }

uint64_t QNodeEditorTreeModel::addNode()
{
    beginInsertRows({}, rowCount(), rowCount());

    uint64_t id = idCounter++;
    _nodes.emplace(id, new QNodeEditorNode { id });

    endInsertRows();
    return id;
}

void QNodeEditorTreeModel::addConnection(uint64_t from, uint64_t to)
{
    auto fromNode = _nodes.find(from);
    auto toNode = _nodes.find(to);

    if (fromNode == _nodes.end() || toNode == _nodes.end())
        return;

    fromNode->second->connections.push_back(toNode->second);
    fromNode->second->outputPorts.push_back(QNodeEditorNode::Port {
        "connection", false });

    toNode->second->inputPorts.push_back(QNodeEditorNode::Port { "connection",
                                                                 false });

    QModelIndex fromIndex = index(from);

    emit dataChanged(fromIndex, fromIndex, { Connections });
}

int QNodeEditorTreeModel::rowCount(const QModelIndex& parent) const
{
    return idCounter;
}

int QNodeEditorTreeModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QVariant QNodeEditorTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= rowCount())
        return {};

    switch (role) {
        case Qt::DisplayRole: {
            QString connectionsString;
            for (auto& connection :
                 data(index, Connections).value<QList<QNodeEditorNode*>>()) {
                connectionsString.append(QString::number(connection->id));
                connectionsString.append(", ");
            }
            return tr("Node: %1, Connections: %2")
                .arg(data(index, NodeId).toInt())
                .arg(connectionsString);
        }
        case NodeId: return index.row();
        case Connections: {
            QList<QNodeEditorNode*> connections;
            auto& node = _nodes.at(index.row());
            for (auto& connection : node->connections)
                connections.append(connection);
            return QVariant::fromValue<QList<QNodeEditorNode*>>(connections);
        }
        case Color: {
            return QColor { 164, 45, 63, 255 };
        }
        case Inputs: {
            return QVariant::fromValue<QList<QNodeEditorNode::Port>>(
                _nodes.at(index.row())->inputPorts
            );
        }
        case Outputs: {
            return QVariant::fromValue<QList<QNodeEditorNode::Port>>(
                _nodes.at(index.row())->outputPorts
            );
        }
    }
    return {};
}

QVariant QNodeEditorTreeModel::headerData(
    int section, Qt::Orientation orientation, int role
) const
{
    return {};
}

uint64_t QNodeEditorTreeModel::idCounter = 0;
