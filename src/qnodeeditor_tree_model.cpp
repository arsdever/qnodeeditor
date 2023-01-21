#include <QColor>
#include <QRectF>

#include "qnodeeditor_tree_model.hpp"

#include "qnodeeditor/qnodeeditor.hpp"
#include "qnodeeditor/qnodeeditor_connection.hpp"
#include "qnodeeditor/qnodeeditor_node.hpp"
#include "qnodeeditor/qnodeeditor_port.hpp"

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

    emit nodeAdded(index(id, 0));

    endInsertRows();
    return id;
}

void QNodeEditorTreeModel::addConnection(
    uint64_t fromNodeId, uint64_t fromPort, uint64_t toNodeId, uint64_t toPort
)
{
    auto fromNode = _nodes.find(fromNodeId);
    auto toNode = _nodes.find(toNodeId);

    if (fromNode == _nodes.end() || toNode == _nodes.end())
        return;

    while (toNode->second->_inputPorts.size() <= toPort)
        toNode->second->_inputPorts.push_back(new QNodeEditorPort {
            toNode->second,
            static_cast<uint64_t>(toNode->second->_inputPorts.size()),
            PortType::In,
            tr("input %0")
                .arg(toNode->second->_inputPorts.size())
                .toStdString() });

    while (fromNode->second->_outputPorts.size() <= fromPort)
        fromNode->second->_outputPorts.push_back(new QNodeEditorPort {
            fromNode->second,
            static_cast<uint64_t>(fromNode->second->_outputPorts.size()),
            PortType::Out,
            tr("output %0")
                .arg(fromNode->second->_outputPorts.size())
                .toStdString() });

    QNodeEditorConnection* connection =
        new QNodeEditorConnection { fromNode->second->_outputPorts.at(fromPort),
                                    toNode->second->_inputPorts.at(toPort) };
    fromNode->second->_connections.push_back(connection);

    QModelIndex fromIndex = index(fromNodeId);
    QModelIndex toIndex = index(toNodeId);

    emit connectionAdded(connection);
    emit dataChanged(toIndex, toIndex, { Connections });
    emit dataChanged(fromIndex, fromIndex, { Connections });
}

QModelIndex QNodeEditorTreeModel::index(
    int row, int column, const QModelIndex& parent
) const
{
    return createIndex(row, column, _nodes.at(row)->_id);
}

int QNodeEditorTreeModel::rowCount(const QModelIndex& parent) const
{
    return idCounter;
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
                case 0: return tr("Node %0").arg(_nodes.at(index.row())->_id);
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
            auto& node = _nodes.at(index.row());
            return QVariant::fromValue<QList<QNodeEditorConnection*>>(
                node->_connections
            );
        }
        case Color: {
            return QColor { 164, 45, 63, 255 };
        }
        case Inputs: {
            return QVariant::fromValue<QList<QNodeEditorPort*>>(
                _nodes.at(index.row())->_inputPorts
            );
        }
        case Outputs: {
            return QVariant::fromValue<QList<QNodeEditorPort*>>(
                _nodes.at(index.row())->_outputPorts
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
