#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QtWidgets/QAbstractScrollArea>
#include <QtWidgets/QStyle>
#include <QtWidgets/QStyleOptionViewItem>

#include "../../core/tree.h"


#include <QLineEdit>


class TreeModel;

class TreeView : public QAbstractScrollArea
{
	Q_OBJECT

	struct NodeInfo
	{
		QObject *obj;
		QRect rect;
		int    row;
		int    level;
	};

	public:
		explicit TreeView(QWidget *parent = 0);

		TreeModel *model() const;
		void setModel(TreeModel *model);

	protected:
		QSize cellSizeHint(int row, int col, QObject *obj) const;

		void drawCell(int row, int col, QObject *obj, const QRect &cell, QStyleOptionViewItem &opt, QPainter &painter);
		void drawRow(int row, QObject *obj,  const QRect &rect, QStyleOptionViewItem &opt, QPainter &painter);

		int drawNode(int row, QObject *obj);

		void drawTree(QPainter &painter);

		void keyPressEvent(QKeyEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mousePressEvent(QMouseEvent *event);

		void paintEvent(QPaintEvent *event);
		void resizeEvent(QResizeEvent *event);

		void scrollContentsBy(int dx, int dy);

	private:
		int findTopNode(int dy);
		void makePaintList(const QSize &viewport);
		void calculateTotalHeight(void);
		void selectRow(const QPoint &pos, const bool append);

		bool isObjectVisible(QObject *obj);

		void scrollUpToObject(QObject *obj);
		void scrollDownToObject(QObject *obj);

		QObject *objAtPos(const QPoint &pos) const;

		QObject *previousNode(QObject *obj, int &level) const;
		QObject *nextNode(QObject *obj, int &level) const;

		QLineEdit *le;

		QList<NodeInfo> _paintList;
		int _offsetY;

		int _totalHeight;

		QObject *_highlightedItem;
		QList<QObject *> _selectedItems;
		TreeModel *_model;
};

#endif // TREEVIEW_H
