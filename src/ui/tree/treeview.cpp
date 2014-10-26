#include "treeview.h"

#include <QtGui/QGuiApplication>

#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>

#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStyle>
#include <QtWidgets/QStyleOptionFocusRect>

#include "treemodel.h"

#include <QDebug>

TreeView::TreeView(QWidget *parent) :
    QAbstractScrollArea (parent)
{
	setMouseTracking(true);
}

TreeModel *TreeView::model() const
{
	return _model;
}

void TreeView::setModel(TreeModel *model)
{
	_model = model;

	_highlightedItem = 0;
	_selectedItems.clear();

	_offsetY = 0;
	_paintList.clear();
	_paintList.append(NodeInfo());
	_paintList.last().obj = model->root();
	_paintList.last().row = 0;
	_paintList.last().level = 0;

	calculateTotalHeight();

	verticalScrollBar()->setMaximum( _totalHeight );
}

QSize TreeView::cellSizeHint(int row, int col, QObject *obj) const
{
	return QSize(128, 64);
}

void TreeView::drawCell(int row, int col, QObject *obj, const QRect &cell, QStyleOptionViewItem &opt, QPainter &painter)
{
	QStyleOptionViewItem o(opt);

	o.rect = cell;

	if ( model()->flags(obj) & TreeModel::ItemIsEdited )
	{
		o.text = QString("edited");
		o.state |= QStyle::State_Editing;
	}
	else
	{
		o.text = QString("(%1,%2)").arg(row).arg(col);
		style()->drawControl(QStyle::CE_ItemViewItem, &o, &painter, this);
	}

}

void TreeView::drawRow(int row, QObject *obj, const QRect &rect, QStyleOptionViewItem &opt, QPainter &painter)
{
	QRect cell(rect);

	//drawGap();
	if ( _highlightedItem == obj )
		opt.state |= QStyle::State_MouseOver;

	if ( row % 2 )
		opt.features |= QStyleOptionViewItem::Alternate;
	else
		opt.features &= ~QStyleOptionViewItem::Alternate;

	if ( _selectedItems.contains(obj)  )
		opt.state |= QStyle::State_Selected | QStyle::State_KeyboardFocusChange;
	else
		opt.state &= ~(QStyle::State_Selected | QStyle::State_KeyboardFocusChange);

	style()->drawPrimitive(QStyle::PE_PanelItemViewRow, &opt, &painter, this);

	for(uint i = 0; i < model()->columnCount(obj); i++)
	{
		drawCell(row, i, obj, cell, opt, painter);
		cell.moveLeft( cell.x() + cell.width() );
	}

	if ( _selectedItems.contains(obj)  )
	{
		QStyleOptionFocusRect o;
		o.QStyleOption::operator=(opt);
		o.state |= QStyle::State_KeyboardFocusChange;
		QPalette::ColorGroup cg = QPalette::Normal;
		o.backgroundColor = opt.palette.color(cg, QPalette::Highlight);
		o.rect = opt.rect;
		style()->drawPrimitive(QStyle::PE_FrameFocusRect, &o, &painter, this);
	}
}

void TreeView::drawTree(QPainter &painter)
{
	QRect rect;
	QStyleOptionViewItem opt;

	opt.init(this);
	opt.state &= ~QStyle::State_Selected;
	opt.state &= ~QStyle::State_HasFocus;
	opt.state |= QStyle::State_Active;
	opt.state |= QStyle::State_Enabled;
	opt.state |= QStyle::State_Item;
	opt.features = QStyleOptionViewItem::HasDisplay
	             | QStyleOptionViewItem::HasDecoration;
	opt.displayAlignment = Qt::AlignCenter;
	opt.viewItemPosition = QStyleOptionViewItem::OnlyOne;

	opt.showDecorationSelected = true;

	opt.palette.setCurrentColorGroup(QPalette::Active);

	rect.setY(_offsetY);

	foreach(const NodeInfo &node, _paintList)
	{
		//rect.setX( node.level * 32 );
		//rect.setSize(node.rect.size());

		/*opt.rect.setRect(0, rect.y(), node.level * 32, rect.height() );
		style()->drawPrimitive(QStyle::PE_IndicatorBranch, &opt, &painter, this);*/

		//opt.rect.setRect(rect.x(), rect.y(), viewport()->width(), rect.height());
		opt.rect = node.rect;

		drawRow(node.row, node.obj, node.rect, opt, painter);

		//rect.moveTop( rect.y() + rect.height() );
	}
}

void TreeView::keyPressEvent(QKeyEvent *event)
{
	QObject *t;
	int l;
	TreeModel::Flags flags;

	switch ( event->key() )
	{
		case Qt::Key_Up:
			if ( event->modifiers() != Qt::NoModifier )
				break;

			if ( _selectedItems.empty() )
				break;

			t = _selectedItems.last();
			t = previousNode(t, l);
			if ( !t )
				break;
			_selectedItems.clear();
			_selectedItems.append(t);

			if ( !isObjectVisible(t) )
				scrollUpToObject(t);

			event->accept();
			viewport()->update();
			return;

		case Qt::Key_Down:
			if ( event->modifiers() != Qt::NoModifier )
				break;

			t = ( _selectedItems.empty() ) ? model()->root() : nextNode(_selectedItems.last(), l);

			if ( !t )
				break;

			_selectedItems.clear();
			_selectedItems.append(t);

			if ( !isObjectVisible(t) )
			{
				qDebug() << "not visible";
				t = nextNode(t, l);
				scrollDownToObject(t);
			}

			event->accept();
			viewport()->update();
			return;

		case Qt::Key_Home:
			if ( event->modifiers() != Qt::NoModifier )
				break;

			scrollUpToObject(0);

			_selectedItems.clear();
			if ( !_paintList.empty() && _paintList.front().obj )
				_selectedItems.append(_paintList.front().obj);

			event->accept();
			viewport()->update();
			return;

		case Qt::Key_End:
			if ( event->modifiers() != Qt::NoModifier )
				break;

			scrollDownToObject(0);
			_selectedItems.clear();
			if ( !_paintList.empty() && _paintList.last().obj )
				_selectedItems.append(_paintList.last().obj);

			event->accept();
			viewport()->update();
			return;

		case Qt::Key_F2:
			if ( event->modifiers() != Qt::NoModifier )
				break;

			if ( _selectedItems.empty() )
				break;

			t = _selectedItems.last();

			if ( !t )
				break;

			flags = model()->flags(t);

			if ( !(flags & TreeModel::ItemIsEditable) )
				break;

			model()->setFlags( flags | TreeModel::ItemIsEdited, t);

			event->accept();
			viewport()->update();
			return;

		case Qt::Key_Escape:
			if ( event->modifiers() != Qt::NoModifier )
				break;

			if ( _selectedItems.empty() )
				break;

			t = _selectedItems.last();

			if ( !t )
				break;

			flags = model()->flags(t);

			if ( flags & TreeModel::ItemIsEdited )
				flags &= ~TreeModel::ItemIsEdited;
			else if ( flags & TreeModel::ItemIsSelected )
				flags &= ~TreeModel::ItemIsSelected;

			model()->setFlags( flags, t);

			//_selectedItems.clear();

			event->accept();
			viewport()->update();
			return;
	}

	QAbstractScrollArea::keyPressEvent(event);
}

void TreeView::mouseMoveEvent(QMouseEvent *event)
{
	QAbstractScrollArea::mouseMoveEvent(event);

	if ( !hasMouseTracking() )
		return;

	_highlightedItem = objAtPos(event->pos());
	viewport()->update();
	event->accept();
}

void TreeView::mousePressEvent(QMouseEvent *event)
{
	QAbstractScrollArea::mousePressEvent(event);

	if ( event->button() != Qt::LeftButton )
		return;

	selectRow(event->pos(), event->modifiers() & Qt::ControlModifier );
	event->accept();
}

void TreeView::paintEvent(QPaintEvent *event)
{
	QAbstractScrollArea::paintEvent(event);

	QPainter painter(viewport());
	drawTree(painter);
	event->accept();
}

void TreeView::resizeEvent(QResizeEvent *event)
{
	QAbstractScrollArea::resizeEvent(event);

	makePaintList(event->size());
	event->accept();
}

void TreeView::scrollContentsBy(int dx, int dy)
{
	_offsetY = findTopNode(_offsetY + dy);
	makePaintList(viewport()->size());
	viewport()->update();
}

int TreeView::findTopNode(int offset)
{
	QObject *t;
	int level;

	level = _paintList.first().level;

	if ( offset > 0 )
	{
		// scrolling up
		while ( offset > 0 )
		{
			t = previousNode(_paintList.first().obj, level);

			if ( !t )
				return 0;

			_paintList.first().obj = t;
			--_paintList.first().row;
			_paintList.first().level = level;
			_paintList.first().rect.setSize(cellSizeHint(_paintList.first().row, -1, t));

			offset -= _paintList.first().rect.size().height();
		}
	}
	else
	{
		// scrolling down
		while ( abs(offset) > _paintList.first().rect.size().height() )
		{
			offset += _paintList.first().rect.size().height();

			t = nextNode(_paintList.first().obj, level);

			if ( !t )
				return 0;//offset;

			_paintList.first().obj = t;
			++_paintList.first().row;
			_paintList.first().level = level;
			_paintList.first().rect.setSize(cellSizeHint(_paintList.first().row, -1, t));
		}
	}

	return offset;
}

void TreeView::makePaintList(const QSize &viewport)
{
	QObject *obj;
	NodeInfo node;
	int y;
	int row;
	int level;

	int viewportWidth = viewport.width();
	int maxHeight = viewport.height();
	y = _offsetY;

	obj = _paintList.first().obj;
	row = _paintList.first().row;
	level = _paintList.first().level;

	_paintList.clear();

	while ( obj && y < maxHeight )
	{
		_paintList.append(NodeInfo());
		_paintList.last().obj = obj;
		_paintList.last().row = row;
		_paintList.last().level = level;
		_paintList.last().rect.setRect(0, y, viewportWidth, cellSizeHint(row, -1, obj).height());

		row++;
		y += _paintList.last().rect.size().height();

		obj = nextNode(obj, level);
	}
}

void TreeView::calculateTotalHeight()
{
	QObject *t;
	int level;

	t = model()->root();
	_totalHeight = 0;

	while ( (t = nextNode(t, level)) )
		_totalHeight += cellSizeHint(-1, -1, t).height();
}

void TreeView::selectRow(const QPoint &pos, const bool append)
{
	QObject *obj = objAtPos(pos);

	if ( !obj )
		return;

	TreeModel::Flags flags = model()->flags(obj);

	if ( flags & TreeModel::ItemIsSelectable )
	{
		if ( !append )
			_selectedItems.clear();

		_selectedItems.append(obj);
		viewport()->update();
	}
}

bool TreeView::isObjectVisible(QObject *obj)
{
	int height = viewport()->height() - _offsetY;

	foreach(const NodeInfo &node, _paintList)
	{
		qDebug() << "height" << height << node.rect.size().height();

		if ( node.obj == obj )
			return (height > node.rect.size().height());

		height -= node.rect.size().height();
	}

	qDebug() << "height" << height;

	return false;
}

void TreeView::scrollUpToObject(QObject *obj)
{
	int row;
	int level;
	QObject *t;

	int v = verticalScrollBar()->value();

	while ( _paintList.front().obj != obj )
	{
		row   = _paintList.front().row - 1;
		level = _paintList.front().level;

		t = previousNode(_paintList.front().obj, level);

		if ( !t )
			break;

		_paintList.push_front(NodeInfo());
		_paintList.front().obj = t;
		_paintList.front().row = row;
		_paintList.front().level = level;
		_paintList.front().rect.setSize(cellSizeHint(row, -1, t));

		v -= _paintList.front().rect.size().height();

		_paintList.pop_back();
	}

	_offsetY = 0;
	verticalScrollBar()->setValue(v);
}

void TreeView::scrollDownToObject(QObject *obj)
{
	int row;
	int level;
	QObject *t;

	int v = verticalScrollBar()->value();

	while ( _paintList.last().obj != obj )
	{
		row   = _paintList.last().row + 1;
		level = _paintList.last().level;

		t = nextNode(_paintList.last().obj, level);

		if ( !t )
			break;

		_paintList.append(NodeInfo());
		_paintList.last().obj = t;
		_paintList.last().row = row;
		_paintList.last().level = level;
		_paintList.last().rect.setSize(cellSizeHint(row, -1, t));

		v += _paintList.last().rect.size().height();

		_paintList.pop_front();
	}

	// adjust


	//_offsetY = 0;
	verticalScrollBar()->setValue(v);
}

QObject *TreeView::objAtPos(const QPoint &pos) const
{
	int height = pos.y() - _offsetY;

	foreach(const NodeInfo &node, _paintList)
	{
		if ( height < node.rect.size().height() )
			return node.obj;

		height -= node.rect.size().height();
	}

	return 0;
}

QObject *TreeView::previousNode(QObject *obj, int &level) const
{
	QObject *t;

	t = model()->previousSibling(obj);
	if ( t )
	{
		obj = t;
		t = model()->lastChild(t);
		if ( t )
		{
			++level;
			return t;
		}
		else
			return obj;
	}
	else
	{
		--level;
		return model()->parent(obj);
	}
}

QObject *TreeView::nextNode(QObject *obj, int &level) const
{
	QObject *t;

	t = model()->firstChild(obj);
	if ( t )
	{
		++level;
		return t;
	}

	t = model()->nextSibling(obj);
	if ( t )
		return t;

	--level;
	return model()->nextSibling(model()->parent(obj));
}
