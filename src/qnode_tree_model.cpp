#include <qnodeeditor/qnode_tree_model.hpp>

QNodeEditorTreeModel::QNodeEditorTreeModel(QObject *parent)
	: QAbstractItemModel(parent) {}

QNodeEditorTreeModel::~QNodeEditorTreeModel() {}

QModelIndex QNodeEditorTreeModel::index(int row, int column,
										const QModelIndex &parent) const {
	return {};
}

QModelIndex QNodeEditorTreeModel::parent(const QModelIndex &child) const {
	return {};
}

int QNodeEditorTreeModel::rowCount(const QModelIndex &parent) const {
	return 0;
}

int QNodeEditorTreeModel::columnCount(const QModelIndex &parent) const {
	return 0;
}

QVariant QNodeEditorTreeModel::data(const QModelIndex &index, int role) const {
	return {};
}

bool QNodeEditorTreeModel::setData(const QModelIndex &index,
								   const QVariant &value, int role) {
	return false;
}

Qt::ItemFlags QNodeEditorTreeModel::flags(const QModelIndex &index) const {
	return {};
}

QVariant QNodeEditorTreeModel::headerData(int section,
										  Qt::Orientation orientation,
										  int role) const {
	return {};
}

