#include "treeview.h"

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
}

void TreeView::drawCell(int col, const QObject *obj)
{

}

void TreeView::drawRow(const QObject *obj)
{

}

void TreeView::drawTree()
{

}

void TreeView::paintEvent(QPaintEvent *event)
{
	qDebug() << "paint event";
}
