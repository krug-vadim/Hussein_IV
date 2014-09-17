#include "treemodel.h"

#include <QDebug>

TreeModel::TreeModel(const TreeElement &root, QObject *parent)
    : _root(root)
    , QAbstractItemModel(parent)
{
	qDebug() << _root.size();
}

TreeModel::~TreeModel()
{
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if ( !hasIndex(row, column, parent) )
		return QModelIndex();

	qDebug() << "index" << row << column;

	return createIndex(row, column, (void *)&getTask(parent)[row]);
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
	if ( !index.isValid() )
		return QModelIndex();

	qDebug() << "parent" << index.row() << index.column();

	const TreeElement *parent = getTask(index)->parent();

	if ( !parent )
		return QModelIndex();

	return createIndex(parent->row(), 0, (void *)&parent);
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
	const TreeElement *node;

	if ( !index.isValid() )
		return QVariant();

	node = getTask(index);

	switch ( role )
	{
		case Qt::DisplayRole:
			if ( index.column() == 0 )
				return node->value();//( task->description().isEmpty() ) ? tr("(empty)") : task->description();
			break;

		case Qt::EditRole:
			if ( index.column() == 0 )
				return  node->value();//task->description();
			break;

//		default:
//			return task->data(role);
//			break;
	}

	return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
	if ( !index.isValid() )
		return 0;

	return /*Qt::ItemIsEditable
	     | */Qt::ItemIsEnabled
	     | Qt::ItemIsSelectable
	     //| Qt::ItemIsDragEnabled
	     //| Qt::ItemIsDropEnabled
	     ;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		switch ( section )
		{
			case 0 : return tr("Task"); break;
			default: return QVariant(); break;
		}
	}

	return QVariant();
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
	return getTask(parent)->size();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return 1;
}

const TreeElement *TreeModel::getTask(const QModelIndex &index) const
{
	return ( index.isValid() ) ? static_cast<TreeElement *>(index.internalPointer()) : &_root;
}
