#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QtCore/QObject>

class TreeModel : public QObject
{
	Q_OBJECT

	public:
		explicit TreeModel(QObject *parent = 0);
		virtual ~TreeModel();

		virtual QObject *root() =0;
		virtual QObject *parent(const QObject *obj) =0;

		virtual QObject *nextSibling(const QObject *obj) =0;
		virtual QObject *previousSibling(const QObject *obj) =0;

		virtual QObject *firstChild(const QObject *obj) =0;
		virtual QObject *lastChild(const QObject *obj) =0;

		virtual quint64 childCount(const QObject *obj) =0;
		virtual quint64 columnCount(const QObject *obj) =0;

		virtual quint64 flags(const QObject *obj) =0;

	signals:

	public slots:

};

#endif // TREEMODEL_H
