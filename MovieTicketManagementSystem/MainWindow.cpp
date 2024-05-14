#include "MainWindow.h"
#include <QStringListModel>
#include "Movie.h"
#include <MovieListView.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    movieListView = new MovieListView(ui.listView);

}

MainWindow::~MainWindow()
{}

void MainWindow::changeToMainWindow()
{
    	ui.stackedWidget->setCurrentWidget(ui.mainWindow);
}

void MainWindow::changeToManageMovieWindow()
{
		ui.stackedWidget->setCurrentWidget(ui.manageMovieWindow);
}
