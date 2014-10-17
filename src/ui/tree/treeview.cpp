#include "treeview.h"

#include <QtGui/QGuiApplication>

#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>

#include <QtWidgets/QScrollBar>

#include "treemodel.h"

#include <QDebug>

TreeView::TreeView(QWidget *parent) :
    QAbstractScrollArea (parent)
{
}

TreeModel *TreeView::model() const
{
	return _model;
}

void TreeView::setModel(TreeModel *model)
{
	_model = model;

	_selectedItems.clear();

	_offsetY = 0;
	_topNode.obj = model->root();
	_topNode.row = 0;
	_topNode.size = cellSizeHint(0,-1,_topNode.obj);

	calculateTotalHeight();

	verticalScrollBar()->setMaximum( _totalHeight );
}

QSize TreeView::cellSizeHint(int row, int col, const QObject *obj) const
{
	return QSize(128, 16);
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

	if ( row % 2 )
		painter.setBrush( QGuiApplication::palette().brush(QPalette::Midlight) );
	else
		painter.setBrush( QGuiApplication::palette().brush(QPalette::Base)  );

	if ( _selectedItems.contains(obj) )
		painter.setBrush( QGuiApplication::palette().brush(QPalette::Highlight)  );

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

void TreeView::mousePressEvent(QMouseEvent *event)
{
	QAbstractScrollArea::mousePressEvent(event);

	if ( event->button() != Qt::LeftButton )
		return;

	selectRow(event->pos(), event->modifiers() & Qt::ControlModifier );
}

void TreeView::paintEvent(QPaintEvent *event)
{
	qDebug() << "paint event" << verticalScrollBar()->value();
	qDebug() << "viewport" << viewport()->size();

	QAbstractScrollArea::paintEvent(event);

	QPainter painter(viewport());
	drawTree(painter);
}

void TreeView::resizeEvent(QResizeEvent *event)
{
	QAbstractScrollArea::resizeEvent(event);
	makePaintList(event->size());
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

	if ( offset > 0 )
	{
		// scrolling up
		while ( offset > 0 )
		{
			t = previousNode(_topNode.obj);

			if ( !t )
				return 0;

			_topNode.obj = t;
			_topNode.row--;
			_topNode.size = cellSizeHint(_topNode.row, -1, t);

			offset -= _topNode.size.height();
		}
	}
	else
	{
		// scrolling down
		while ( abs(offset) > _topNode.size.height() )
		{
			offset += _topNode.size.height();

			t = nextNode(_topNode.obj);

			if ( !t )
				return offset;

			_topNode.obj = t;
			_topNode.row++;
			_topNode.size = cellSizeHint(_topNode.row, -1, t);
		}
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

void TreeView::calculateTotalHeight()
{
	QObject *t;

	t = model()->root();
	_totalHeight = 0;

	while ( (t = nextNode(t)) )
		_totalHeight += cellSizeHint(-1, -1, t).height();
}

void TreeView::selectRow(const QPoint &pos, const bool append)
{
	int height = pos.y();

	foreach(const NodeInfo &node, _paintList)
	{
		if ( height < node.size.height() )
		{
			TreeModel::Flags flags;

			flags = model()->flags(node.obj);

			if ( flags & TreeModel::ItemIsSelectable )
			{
				if ( !append )
					_selectedItems.clear();

				_selectedItems.append(node.obj);
				viewport()->update();
			}
			return;
		}

		height -= node.size.height();
	}
}

QObject *TreeView::previousNode(QObject *obj) const
{
	QObject *t;

	t = model()->previousSibling(obj);
	if ( t )
	{
		obj = t;
		t = model()->lastChild(t);
		return t ? t : obj;
	}
	else
		return model()->parent(obj);
}

QObject *TreeView::nextNode(QObject *obj) const
{
	QObject *t;

	t = model()->firstChild(obj);
	if ( t )
		return t;

	t = model()->nextSibling(obj);
	if ( t )
		return t;

	return model()->nextSibling(model()->parent(obj));
}
