#ifndef TESTTREEMODEL_H
#define TESTTREEMODEL_H

#include <QtCore/QVector>

#include "tree/treemodel.h"

class TestObject : public QObject
{
	Q_OBJECT

	public:
		TestObject(QObject *parent = 0) : QObject(parent)
		{
			flags = TreeModel::ItemIsSelectable;
		}

		TreeModel::Flags flags;
};

class TestTreeModel : public TreeModel
{
	Q_OBJECT

	public:
		explicit TestTreeModel(QObject *root = 0, QObject *parent = 0);

		virtual QObject *root();
		virtual QObject *parent(const QObject *obj);

		virtual QObject *nextSibling(const QObject *obj);
		virtual QObject *previousSibling(const QObject *obj);

		virtual QObject *firstChild(const QObject *obj);
		virtual QObject *lastChild(const QObject *obj);

		virtual quint64 childCount(const QObject *obj);
		virtual quint64 columnCount(const QObject *obj);

		virtual Flags flags(const QObject *obj);
		virtual void setFlags(Flags flags, QObject *obj);

	private:
		int getNum(const QObject *obj);

		TestObject *_root;
		QVector<TestObject *> _nodes;

};

#endif // TESTTREEMODEL_H
