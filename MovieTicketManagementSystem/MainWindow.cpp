#include "MainWindow.h"
#include "MovieDatabase.h"
#include "MovieTableWidget.h"
#include "ManageMovieWindow.h"
#include "ManageScheduleWindow.h"
#include "SelectMovieWindow.h"
#include "SelectScheduleWindow.h"
#include <QMessageBox>
#include <QStringListModel>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
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
    bookTicketWindow = new BookTicketWindow(selectMovieWindow,selectScheduleWindow,reserveSeatsWindow,inputPersonalDataWindow);
    bookingTableWidget = new BookingTableWidget(ui.manageBookingTableWidget);
    manageBookingWindow = new ManageBookingWindow(ui.titleBookingComboBox, ui.scheduleBookingComboBox, ui.seatManageLineEdit, ui.nameManageLineEdit, ui.surnameManageLineEdit, ui.emailManageLineEdit,ui.saveBookingButton, ui.removeBookingButton, ui.manageBookingTableWidget);

    //connections to refresh lists in windows
    connect(manageMovieWindow, &ManageMovieWindow::moviesChanged, manageScheduleWindow, &ManageScheduleWindow::refreshSchedules);

    //refresh movie list in select movie window after changes
    connect(manageMovieWindow, &ManageMovieWindow::moviesChanged, selectMovieWindow, &SelectMovieWindow::setMoviesInTableWidget);
    
    //refresh booking list after changes
    connect(manageScheduleWindow, &ManageScheduleWindow::schedulesChanged, manageBookingWindow, &ManageBookingWindow::refreshBookings);

    //after changes in file for room , refresh room in reserve seats window
    connect(manageRoomWindow, &ManageRoomWindow::fileSaved, reserveSeatsWindow, &ReserveSeatsWindow::reloadSeatData);

    //connections from book tickets windows
    connect(selectMovieWindow, &SelectMovieWindow::movieSelected, this, &MainWindow::changeToSelectScheduleWindow);
    connect(selectScheduleWindow, &SelectScheduleWindow::scheduleSelected, this, &MainWindow::changeToReserveSeatsWindow);
}

MainWindow::~MainWindow() {
    delete movieTableWidget;
    delete showScheduleTable;
    delete manageScheduleWindow;
    delete manageRoomWindow;
    delete manageMovieWindow;
    delete selectMovieWindow;
    delete selectScheduleWindow;
    delete reserveSeatsWindow;
    delete inputPersonalDataWindow;
    delete bookTicketWindow;
    delete bookingTableWidget;
    delete manageBookingWindow;
}

void MainWindow::changeToMainWindow() {
    ui.stackedWidget->setCurrentWidget(ui.mainWindow);
}

void MainWindow::changeToManageScheduleWindow() {
    ui.stackedWidget->setCurrentWidget(ui.manageScheduleWindow);
}

void MainWindow::changeToSelectMovieWindow() {
    ui.stackedWidget->setCurrentWidget(ui.selectMovieWindow);
}

void MainWindow::changeToSelectScheduleWindow() {
    if (selectMovieWindow->getSelectedMovieId() != -1) {
        selectScheduleWindow->setSchedulesInTableWidget(selectMovieWindow->getSelectedMovieId());
        selectScheduleWindow->setMovieId(selectMovieWindow->getSelectedMovieId());
        ui.stackedWidget->setCurrentWidget(ui.selectScheduleWindow);
    }
}

void MainWindow::changeToReserveSeatsWindow() {
    if (selectScheduleWindow->getSelectedScheduleId() != -1) {
        ui.stackedWidget->setCurrentWidget(ui.reserveSeatsWindow);
    }   	
}

void MainWindow::changeToInputPersonalDataWindow() {
    if (reserveSeatsWindow->isSeatReserved())
    {
		ui.stackedWidget->setCurrentWidget(ui.inputPersonalDataWindow);
	}   
}

void MainWindow::changeToShowScheduleWindow() {
    showScheduleTable->setSchedulesInTableWidget();
    ui.stackedWidget->setCurrentWidget(ui.showScheduleWindow);
}

void MainWindow::changeToManageMovieWindow() {
    ui.stackedWidget->setCurrentWidget(ui.manageMovieWindow);
}

void MainWindow::changeToBookTicketWindow() {
    ui.stackedWidget->setCurrentWidget(ui.selectMovieWindow);
}

void MainWindow::changeToShowMovieListWindow() {
    movieTableWidget->setMoviesInTableWidget();
    ui.stackedWidget->setCurrentWidget(ui.showMovieListWindow);

}

void MainWindow::changeToViewBookingsWindow() {
    bookingTableWidget->setBookingsInTableWidget();
    ui.stackedWidget->setCurrentWidget(ui.viewBookingsWindow);
}

void MainWindow::changeToManageRoomWindow() {
    ui.stackedWidget->setCurrentWidget(ui.manageRoomWindow);
}
