#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QtWidgets/QAbstractScrollArea>

class TreeModel;

class TreeView : public QAbstractScrollArea
{
	Q_OBJECT

	public:
		explicit TreeView(QWidget *parent = 0);

		TreeModel *model() const;
		void setModel(TreeModel *model);

	private:
		TreeModel *_model;
};

#endif // TREEVIEW_H
