#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "testtreemodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	qDebug() << sizeof(QObject);

	ui->widget->setModel(new TestTreeModel(0, this));
	//ui->treeView->setUniformRowHeights(true);
	//ui->treeView->setModel(new TreeModel(t));

	//ui->tableView->setModel(new TreeModel(t));
}

MainWindow::~MainWindow()
{
	delete ui;
}
