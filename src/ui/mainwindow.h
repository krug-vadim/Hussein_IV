#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

#include "../task/task.h"
#include "../task/yamlserialization.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	public slots:
		void loadTask();

	private:
		std::list<int> some_list;
		TaskSharedPointer _root;

		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
