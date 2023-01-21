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
    fromNode->second->outputPorts.push_back(
        std::make_shared<QNodeEditorPort>("connection", false)
    );

    toNode->second->inputPorts.push_back(
        std::make_shared<QNodeEditorPort>("connection", false)
    );

    QModelIndex fromIndex = index(from);

    emit dataChanged(fromIndex, fromIndex, { Connections });
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
                case 0: return tr("Node %0").arg(_nodes.at(index.row())->id);
                case 1:
                    return index.data(Inputs)
                        .value<QList<std::shared_ptr<QNodeEditorPort>>>()
                        .size();
                case 2:
                    return index.data(Outputs)
                        .value<QList<std::shared_ptr<QNodeEditorPort>>>()
                        .size();
            }
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
            return QVariant::fromValue<QList<std::shared_ptr<QNodeEditorPort>>>(
                _nodes.at(index.row())->inputPorts
            );
        }
        case Outputs: {
            return QVariant::fromValue<QList<std::shared_ptr<QNodeEditorPort>>>(
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
