#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtWidgets/QFileDialog>

#include "testtreemodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	_root = TaskSharedPointer(new Task());
	_root->setParent(TaskSharedPointer());
	_root->setDescription(tr("(root)"));

	connect(ui->actionOpen, SIGNAL(triggered()),
	        this, SLOT(loadTask()));

	ui->widget->setModel(new TestTreeModel(0, this));
	ui->widget->setFocus();
	//ui->treeView->setUniformRowHeights(true);
	//ui->treeView->setModel(new TreeModel(t));

	//ui->tableView->setModel(new TreeModel(t));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::loadTask()
{
	QStringList fileNames = QFileDialog::getOpenFileNames(this,
	                                                      tr("Open tasklist(s)..."),
	                                                      QString(),
	                                                      tr("Tasklist (*.yml);;Any (*.*)"));

	if ( fileNames.empty() )
		return;

	int index;

	foreach(const QString &fileName, fileNames)
	{
		if ( fileName.isEmpty() )
			continue;

		YamlSerialization::deserialize(fileName, _root);
	}
}
