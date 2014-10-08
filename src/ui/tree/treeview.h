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

	protected:
		void drawCell(int col, const QObject *obj);
		void drawRow(const QObject *obj);
		void drawTree();

		void paintEvent(QPaintEvent * event);

	private:
		TreeModel *_model;
};

#endif // TREEVIEW_H
