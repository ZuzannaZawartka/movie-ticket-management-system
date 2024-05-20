#include "MainWindow.h"
#include "MovieDatabase.h"
#include "MovieTableWidget.h"
#include "ManageMovieWindow.h"
#include "ManageScheduleWindow.h"
#include "SelectMovieWindow.h"
#include "SelectScheduleWindow.h"
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
    selectMovieWindow = new SelectMovieWindow(ui.acceptBookTicket1Button, ui.selectMovieTableWidget);
    selectScheduleWindow = new SelectScheduleWindow(ui.acceptBookTicket2Button, ui.selectScheduleTableWidget);
    reserveSeatsWindow = new ReserveSeatsWindow(ui.reserveSeatsGrid,ui.acceptBookTicket3Button);
    inputPersonalDataWindow = new InputPersonalDataWindow(ui.nameLineEdit, ui.surnameLineEdit, ui.emailLineEdit,ui.movieLineEdit,ui.dateTimeEdit,ui.amountTicketSpinBox,ui.acceptBookTicket4Button);
    bookTicketWindow = new BookTicketWindow(selectMovieWindow,selectScheduleWindow,reserveSeatsWindow);


    //connections to refresh lists in windows
    connect(manageMovieWindow, &ManageMovieWindow::movieAdded, manageScheduleWindow, &ManageScheduleWindow::refreshSchedules);
    connect(manageMovieWindow, &ManageMovieWindow::movieRemoved, manageScheduleWindow, &ManageScheduleWindow::refreshSchedules);
    
    //connections from book tickets windows
    connect(selectMovieWindow, &SelectMovieWindow::movieSelected, this, &MainWindow::changeToSelectScheduleWindow);
    connect(selectScheduleWindow, &SelectScheduleWindow::scheduleSelected, this, &MainWindow::changeToReserveSeatsWindow);
}

MainWindow::~MainWindow()
{
    delete movieTableWidget;
    delete manageMovieWindow;
    delete showScheduleTable;
    delete manageScheduleWindow;
    delete manageRoomWindow;
    delete reserveSeatsWindow;
    delete selectMovieWindow;
   // delete selectScheduleWindow;
   // delete bookTicketWindow;


}

void MainWindow::changeToMainWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.mainWindow);
}

void MainWindow::changeToManageScheduleWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.manageScheduleWindow);
}

void MainWindow::changeToSelectMovieWindow()
{
    selectMovieWindow->resetSelectedMovieId();
    ui.stackedWidget->setCurrentWidget(ui.selectMovieWindow);
}

void MainWindow::changeToSelectScheduleWindow()
{
    selectScheduleWindow->resetSelectedScheduleId();

    if (selectMovieWindow->getSelectedMovieId() != -1)
    {
        selectScheduleWindow->setSchedulesInTableWidget(selectMovieWindow->getSelectedMovieId());
        selectScheduleWindow->setMovieId(selectMovieWindow->getSelectedMovieId());
        ui.stackedWidget->setCurrentWidget(ui.selectScheduleWindow);
    }
}

void MainWindow::changeToReserveSeatsWindow()
{
    if (selectScheduleWindow->getSelectedScheduleId() != -1) {
        ui.stackedWidget->setCurrentWidget(ui.reserveSeatsWindow);
    }   	
}

void MainWindow::changeToInputPersonalDataWindow()
{
    if (reserveSeatsWindow->isSeatReserved())
    {
		ui.stackedWidget->setCurrentWidget(ui.inputPersonalDataWindow);
	}   
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
