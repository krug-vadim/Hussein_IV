#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QtCore/QAbstractItemModel>

#include "../../core/tree.h"

template<class T>
class TreeModel : public QAbstractItemModel
{
	Q_OBJECT

	public:
		explicit TreeModel(const Tree<T> &tree, QObject *parent = 0);
		~TreeModel();

		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;

		QVariant data(const QModelIndex &index, int role) const;
		Qt::ItemFlags flags(const QModelIndex &index) const;

		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;

	protected:
		Tree<T> tree(const QModelIndex &index) const;

	private:
		Tree<T> _tree;
};

#endif // TREEMODEL_H
