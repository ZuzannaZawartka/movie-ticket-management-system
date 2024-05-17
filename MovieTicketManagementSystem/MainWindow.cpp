#include "MainWindow.h"
#include <QStringListModel>
#include "Movie.h"
#include "MovieListView.h"
#include "AddMovieWindow.h"
#include "Schedule.h"
#include "ScheduleListView.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    scheduleListView = new ScheduleListView(ui.ScheduleListView);
    movieListView = new MovieListView(ui.MovieListView);
    bookTicketListView = new MovieListView(ui.bookTicketListView);
    removeMovieListView = new MovieListView(ui.removeMovieListView);
    addMovieWindow = new AddMovieWindow(ui.textTitleEdit, ui.textDirectorEdit, ui.chooseMovieTypeBox, ui.timeDurationLineEdit, ui.addMovieToDatabase, movieListView);
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
    ui.stackedWidget->setCurrentWidget(ui.showMovieListWindow);
}
void MainWindow::changeToViewBookingsWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.viewBookingsWindow);
}
void MainWindow::changeToAddMovieWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.addMovieWindow);

}
void MainWindow::changeToRemoveMovieWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.removeMovieWindow);
}
