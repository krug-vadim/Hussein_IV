#ifndef TESTTREEMODEL_H
#define TESTTREEMODEL_H

#include <QtCore/QVector>

#include "tree/treemodel.h"

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

		virtual quint64 flags(const QObject *obj);

	private:
		int getNum(const QObject *obj);

		QObject *_root;
		QVector<QObject *> _nodes;

};

#endif // TESTTREEMODEL_H
