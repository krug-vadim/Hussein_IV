#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../core/tree.h"

#include "models/treemodel.h"

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

	ui->treeView->setModel(new TreeModel(t));
}

MainWindow::~MainWindow()
{
	delete ui;
}
