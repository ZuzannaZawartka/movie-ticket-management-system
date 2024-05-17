#include "MainWindow.h"
#include "MovieDatabase.h"
#include "MovieTableWidget.h"
#include "ManageMovieWindow.h"
#include <QMessageBox>
#include <QStringListModel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    movieTableWidget = new MovieTableWidget(ui.movieTableWidget);
    //scheduleListView = new ScheduleListView(ui.ScheduleListView);
    manageRoomWindow = new ManageRoomWindow(ui.plainTextEditManageRoom,ui.acceptManageRoomButton);
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

void MainWindow::changeToManageRoomWindow()
{
	ui.stackedWidget->setCurrentWidget(ui.manageRoomWindow);
}