#include "treemodel.h"

TreeModel::TreeModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

TreeModel::~TaskModel()
{
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if ( !hasIndex(row, column, parent) )
		return QModelIndex();

	return createIndex(row, column, (void *)&getTask(parent)->subtasks().at(row));
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
	if ( !index.isValid() )
		return QModelIndex();

	TaskWeakPointer parent = getTask(index)->parent();

	if ( parent.isNull() )
		return QModelIndex();

	if ( parent == _root )
		return QModelIndex();

	TaskWeakPointer grandParent = parent.toStrongRef()->parent();
	int parentRow = grandParent.toStrongRef()->subtasks().indexOf(parent);

	if ( parentRow == - 1 )
		return QModelIndex();

	return createIndex(parentRow, 0, (void *)&grandParent.toStrongRef()->subtasks().at(parentRow));
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
	TaskSharedPointer task;

	if ( !index.isValid() )
		return QVariant();

	task = getTask(index);

	switch ( role )
	{
		case Qt::DisplayRole:
			if ( index.column() == 0 )
				return ( task->description().isEmpty() ) ? tr("(empty)") : task->description();
			break;

		case Qt::EditRole:
			if ( index.column() == 0 )
				return task->description();
			break;

		default:
			return task->data(role);
			break;
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
	return getTask(parent)->subtasks().size();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return 1;
}

TaskSharedPointer TreeModel::getTask(const QModelIndex &index) const
{
	return ( index.isValid() ) ? *static_cast<TaskSharedPointer *>(index.internalPointer()) : _root;
}
