#include "MainWindow.h"
#include "MovieDatabase.h"
#include "MovieTableWidget.h"
#include "ManageMovieWindow.h"
#include "ManageScheduleWindow.h"
#include "SelectMovieWindow.h"
#include <QMessageBox>
#include <QStringListModel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    movieTableWidget = new MovieTableWidget(ui.movieTableWidget);
    showScheduleTable = new ScheduleTableWidget(ui.showScheduleTable);
    manageScheduleWindow = new ManageScheduleWindow(ui.movieChoose, ui.dateChoose, ui.timeChoose, ui.durationChoose, ui.addScheduleButton, ui.removeScheduleButton, ui.saveScheduleButton, ui.tableScheduleWidget);
    manageRoomWindow = new ManageRoomWindow(ui.plainTextEditManageRoom, ui.acceptManageRoomButton);
    manageMovieWindow = new ManageMovieWindow(ui.textTitleEdit, ui.textDirectorEdit, ui.chooseMovieTypeBox, ui.timeDurationLineEdit, ui.saveMovieButton, ui.addMovieToDatabase, ui.removeMovieButon, ui.manageMovieTableWidget);
    reserveSeatsWindow = new ReserveSeatsWindow(ui.reserveSeatsGrid);
    selectMovieWindow = new SelectMovieWindow(ui.acceptBookTicket1Button, ui.selectMovieTableWidget);

    bookTicketWindow = new BookTicketWindow(selectMovieWindow);

    connect(manageMovieWindow, &ManageMovieWindow::movieAdded, manageScheduleWindow, &ManageScheduleWindow::refreshSchedules);
    connect(manageMovieWindow, &ManageMovieWindow::movieRemoved, manageScheduleWindow, &ManageScheduleWindow::refreshSchedules);
    
}

MainWindow::~MainWindow()
{}


void MainWindow::changeToMainWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.mainWindow);
}

void MainWindow::changeToManageScheduleWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.manageScheduleWindow);
}

void MainWindow::changeToShowScheduleWindow()
{
    showScheduleTable->setSchedulesInTableWidget();
    ui.stackedWidget->setCurrentWidget(ui.showScheduleWindow);
}

void MainWindow::changeToManageMovieWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.manageMovieWindow);
}

void MainWindow::changeToBookTicketWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.selectMovieWindow);
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
