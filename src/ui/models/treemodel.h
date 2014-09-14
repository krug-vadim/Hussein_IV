#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QtCore/QAbstractItemModel>
#include "../../core/tree.h"

typedef Tree<int> TreeElement;

class TreeModel : public QAbstractItemModel
{
	Q_OBJECT

	public:
		typedef QList<int> Path;

		explicit TreeModel(const TreeElement &root, QObject *parent = 0);
		~TreeModel();

		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;

		QVariant data(const QModelIndex &index, int role) const;
		Qt::ItemFlags flags(const QModelIndex &index) const;

		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;

	protected:
		const TreeElement *getTask(const QModelIndex &index) const;

	private:
		const TreeElement _root;
};

#endif // TASKMODEL_H
