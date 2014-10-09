#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QtWidgets/QAbstractScrollArea>

#include "../../core/tree.h"

class TreeModel;

class TreeView : public QAbstractScrollArea
{
	Q_OBJECT

	struct NodeInfo
	{
		int height;
		QObject *obj;
	};

	public:
		explicit TreeView(QWidget *parent = 0);

		TreeModel *model() const;
		void setModel(TreeModel *model);

	protected:
		void drawCell(int row, int col, const QObject *obj, QPainter &painter);
		void drawRow(int row, const QObject *obj, QPainter &painter);

		int drawNode(int row, const QObject *obj);

		void drawTree(QPainter &painter);

		void paintEvent(QPaintEvent * event);

	private:
		TreeModel *_model;

		Tree<NodeInfo> *_rootInfo;
};

#endif // TREEVIEW_H
