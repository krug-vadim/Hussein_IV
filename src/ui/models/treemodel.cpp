#include "treemodel.h"

#include <QtCore/QMimeData>
#include <QtCore/QStringList>

#include <QDebug>

template<class T>
TreeModel<T>::TreeModel(const Tree<T> &tree, QObject *parent)
    : _tree(tree)
    , QAbstractItemModel(parent)
{
}

template<class T>
TreeModel<T>::~TreeModel()
{
}

template<class T>
QModelIndex TreeModel<T>::index(int row, int column, const QModelIndex &parent) const
{
	if ( !hasIndex(row, column, parent) )
		return QModelIndex();

	return createIndex(row, column, (void *)&tree(parent));
}

template<class T>
QModelIndex TreeModel<T>::parent(const QModelIndex &index) const
{
	if ( !index.isValid() )
		return QModelIndex();

	return createIndex(0, 0, tree(index) );
}

template<class T>
QVariant TreeModel<T>::data(const QModelIndex &index, int role) const
{
	if ( !index.isValid() )
		return QVariant();

	switch ( role )
	{
		case Qt::DisplayRole:
			return tree(index)->value();
			/*if ( index.column() == 0 )
				return ( task->description().isEmpty() ) ? tr("(empty)") : task->description();*/
			break;

//		case Qt::EditRole:
//			if ( index.column() == 0 )
//				return task->description();
//			break;

		default:
			break;
	}

	return QVariant();
}

template<class T>
Qt::ItemFlags TreeModel<T>::flags(const QModelIndex &index) const
{
	if ( !index.isValid() )
		return 0;

	return /*Qt::ItemIsEditable*/
	       Qt::ItemIsEnabled
	     | Qt::ItemIsSelectable
	     //| Qt::ItemIsDragEnabled
	     //| Qt::ItemIsDropEnabled
	     ;
}

template<class T>
QVariant TreeModel<T>::headerData(int section, Qt::Orientation orientation, int role) const
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

template<class T>
int TreeModel<T>::rowCount(const QModelIndex &parent) const
{
	return tree(parent)->siblings().size();
}

template<class T>
int TreeModel<T>::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return 1;
}

template<class T>
Tree<T> TreeModel<T>::tree(const QModelIndex &index) const
{
	if ( index.isValid() )
		static_cast<Tree<T> *>(index.internalPointer())->siblings()[index.row()];
	else
		return _tree;
}
