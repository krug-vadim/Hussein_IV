#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../core/tree.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Tree<int> t(69);

	t = t.append(1);
	t = t.append(2);
	t = t.append(3);
	t = t.append(4);

	t = t.append(t);

	quint64 i;
	for(i = 0; i < (10*1000*1000); i++)
		int *p = new int(i);

	QList<int> some = {1,2,3,4,5};
	QVector<int> some2 = {1,2,3,4,5};

	qDebug() << sizeof(QObject);
	//ui->treeView->setUniformRowHeights(true);
	//ui->treeView->setModel(new TreeModel(t));

	//ui->tableView->setModel(new TreeModel(t));
}

MainWindow::~MainWindow()
{
	delete ui;
}
