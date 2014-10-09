#include "treeview.h"

#include <QtGui/QPainter>

#include <QtWidgets/QScrollBar>

#include "treemodel.h"

#include <QDebug>

TreeView::TreeView(QWidget *parent) :
    QAbstractScrollArea (parent)
{
	verticalScrollBar()->setMaximum(100*32);
}

TreeModel *TreeView::model() const
{
	return _model;
}

void TreeView::setModel(TreeModel *model)
{
	_model = model;
}

void TreeView::drawCell(int row, int col, const QObject *obj, QPainter &painter)
{
	//do it
	qDebug() << "drawCell" << row << col;
	painter.drawRect( col * 64,
	                  row * 32,
	                  64,
	                  32);
	painter.drawText(col*64+4,
	                 row*32+16,
	                 QString("(%1,%2)").arg(row).arg(col));
}

void TreeView::drawRow(int row, const QObject *obj, QPainter &painter)
{
	//drawGap();
	for(int i = 0; i < model()->columnCount(obj); i++)
		drawCell(row, i, obj, painter);
}

void TreeView::drawTree(QPainter &painter)
{
	int row;
	QObject *obj;

	row = 0;
	obj = model()->firstChild(model()->root());

	while ( obj )
	{
		drawRow(row++, obj, painter);

		if ( model()->firstChild(obj) )
			obj = model()->firstChild(obj);
		else if ( model()->nextSibling(obj) )
			obj = model()->nextSibling(obj);
		else
			obj = model()->nextSibling(model()->parent(obj));
	}
}

void TreeView::paintEvent(QPaintEvent *event)
{
	qDebug() << "paint event" << verticalScrollBar()->value();

	QAbstractScrollArea::paintEvent(event);

	QPainter painter(viewport());
	drawTree(painter);
	//viewport()->update();
}
