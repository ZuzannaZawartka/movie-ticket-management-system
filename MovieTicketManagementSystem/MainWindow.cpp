#include "MainWindow.h"
#include <QStringListModel>
#include "Movie.h"
#include "MovieTableWidget.h"
#include "ManageMovieWindow.h"
#include "MovieDatabase.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    movieTableWidget = new MovieTableWidget(ui.MovieTableWidget);
    manageMovieWindow = new ManageMovieWindow(ui.textTitleEdit, ui.textDirectorEdit, ui.chooseMovieTypeBox, ui.timeDurationLineEdit,ui.saveMovieButton, ui.addMovieToDatabase,ui.removeMovieButon, ui.manageMovieTableWidget);
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
void MainWindow::changeToBookTicketWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.bookTicketWindow);
}
void MainWindow::changeToShowMovieListWindow()
{   
    movieTableWidget->setMoviesInTableWidget();
    ui.stackedWidget->setCurrentWidget(ui.showMovieListWindow);

}
void MainWindow::changeToViewBookingsWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.viewBookingsWindow);
}
