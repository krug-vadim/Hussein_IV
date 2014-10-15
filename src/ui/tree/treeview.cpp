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

	_offsetY = 0;
	_topNode.obj = model->root();
	_topNode.row = 0;
	_topNode.size = cellSizeHint(0,-1,_topNode.obj);
	verticalScrollBar()->setMaximum( cellSizeHint(-1,-1,model->root()).height() * model->childCount(model->root()) );
}

QSize TreeView::cellSizeHint(int row, int col, const QObject *obj) const
{
	return QSize(64, 32);
}

void TreeView::drawCell(int row, int col, const QObject *obj, const QRect &cell, QPainter &painter)
{
	//do it
	painter.drawRect( cell );
	painter.drawText(cell.x()+4,
	                 cell.y()+16,
	                 QString("(%1,%2)").arg(row).arg(col));
}

void TreeView::drawRow(int row, const QObject *obj, const QRect &rect, QPainter &painter)
{
	QRect cell(rect);

	//drawGap();
	for(int i = 0; i < model()->columnCount(obj); i++)
	{
		drawCell(row, i, obj, cell, painter);
		cell.moveLeft( cell.x() + cell.width() );
	}
}

void TreeView::drawTree(QPainter &painter)
{
	QRect rect;

	rect.setX(0);
	rect.setY(_offsetY);

	foreach(const NodeInfo &node, _paintList)
	{
		rect.setSize(node.size);
		drawRow(node.row, node.obj, rect, painter);
		rect.moveTop( rect.y() + rect.height() );
	}
}

void TreeView::paintEvent(QPaintEvent *event)
{
	qDebug() << "paint event" << verticalScrollBar()->value();
	qDebug() << "viewport" << viewport()->size();

	QAbstractScrollArea::paintEvent(event);

	QPainter painter(viewport());
	drawTree(painter);
	//viewport()->update();
}

void TreeView::scrollContentsBy(int dx, int dy)
{
	qDebug() << "scrollBy" << dx << dy;

	_offsetY = findTopNode(_offsetY + dy);
	makePaintList(viewport()->size());
	viewport()->update();
}

int TreeView::findTopNode(int offset)
{
	QObject *t;
	QSize size;

	if ( offset == 0)
		return 0;
	else if ( offset < 0 ) // scrolling down
	{
		if ( abs(offset) > _topNode.size.height() )
		{
			offset += _topNode.size.height();

			t = nextNode(_topNode.obj);

			if ( t )
			{
				_topNode.obj = t;
				_topNode.row++;
			}
			else
			{
				_topNode.obj = model()->root();
				_topNode.row = 0;
			}

			_topNode.size = cellSizeHint(_topNode.row, -1, t);

			return findTopNode(offset);
		}
		else
			return offset;
	}
	else // scrolling up
	{
		t = previousNode(_topNode.obj);

		if ( t )
			size = cellSizeHint(_topNode.row-1, -1, t);
		else
			size = cellSizeHint(-1, -1, model()->root());

		if ( abs(offset) > size.height() )
		{
			offset -= size.height();
			_topNode.size = size;

			if ( t )
			{
				_topNode.obj = t;
				_topNode.row--;

				return findTopNode(offset);
			}
			else
			{
				_topNode.obj = model()->root();
				_topNode.row = 0;
				return 0;
			}
		}
		else
			return offset;
	}

	return offset;
}

void TreeView::makePaintList(const QSize &viewport)
{
	QObject *obj;
	int remainHeight;
	int row;

	remainHeight = viewport.height() - _offsetY;

	row = _topNode.row;
	obj = _topNode.obj;

	_paintList.clear();

	while ( obj && remainHeight > 0 )
	{
		_paintList.append(NodeInfo());
		_paintList.last().obj = obj;
		_paintList.last().row = row;
		_paintList.last().size = cellSizeHint(row, -1, obj);

		row++;
		remainHeight -= _paintList.last().size.height();

		obj = nextNode(obj);
	}
}

QObject *TreeView::previousNode(QObject *obj) const
{
	QObject *t;

	while ( obj )
	{
		t = model()->previousSibling(obj);
		if ( t )
		{
			obj = t;
			t = model()->lastChild(obj);
			return t ? t : obj;
		}

		obj = model()->parent(obj);
	}

	return obj;
}

QObject *TreeView::nextNode(QObject *obj) const
{
	QObject *t;

	while ( obj )
	{
		t = model()->firstChild(obj);
		if ( t )
			return t;

		t = model()->nextSibling(obj);
		if ( t )
			return t;

		obj = model()->parent(obj);
	}

	return obj;
}
