#include "treeview.h"

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
