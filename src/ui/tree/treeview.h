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
		QObject *obj;
		QSize   size;
		int     row;
	};

	public:
		explicit TreeView(QWidget *parent = 0);

		TreeModel *model() const;
		void setModel(TreeModel *model);

	protected:
		QSize cellSizeHint(int row, int col, const QObject *obj) const;

		void drawCell(int row, int col, const QObject *obj, const QRect &cell, QPainter &painter);
		void drawRow(int row, const QObject *obj,  const QRect &rect, QPainter &painter);

		int drawNode(int row, const QObject *obj);

		void drawTree(QPainter &painter);

		void mousePressEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);
		void resizeEvent(QResizeEvent *event);

		void scrollContentsBy(int dx, int dy);

	private:
		int findTopNode(int dy);
		void makePaintList(const QSize &viewport);
		void calculateTotalHeight(void);
		void selectRow(const QPoint &pos, const bool append);

		QObject *previousNode(QObject *obj) const;
		QObject *nextNode(QObject *obj) const;

		QList<NodeInfo> _paintList;
		NodeInfo _topNode;
		int _offsetY;

		int _totalHeight;

		QList<const QObject *> _selectedItems;
		TreeModel *_model;
};

#endif // TREEVIEW_H
