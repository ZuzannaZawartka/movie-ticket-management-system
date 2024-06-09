#include "BookTicketWindow.h"
#include "BookingDatabase.h"
#include "InputPersonalDataWindow.h"
#include "ReserveSeatsWindow.h"
#include "SelectMovieWindow.h"
#include "SelectScheduleWindow.h"
#include "Seat.h"
#include <QMessageBox>

BookTicketWindow::BookTicketWindow(SelectMovieWindow* selectMovieWindow, SelectScheduleWindow* selectScheduleWindow, ReserveSeatsWindow* reserveSeatsWindow, InputPersonalDataWindow* inputPersonalDataWindow)
    : selectMovieWindow(selectMovieWindow),
    selectScheduleWindow(selectScheduleWindow),
    reserveSeatsWindow(reserveSeatsWindow),
    inputPersonalDataWindow(inputPersonalDataWindow) {

    movieID = -1;
	scheduleID = -1;
    name = "";
    surname = "";
    email = "";

    connect(selectMovieWindow, &SelectMovieWindow::movieSelected, this, &BookTicketWindow::onMovieAccepted);
    connect(selectScheduleWindow, &SelectScheduleWindow::scheduleSelected, this, &BookTicketWindow::onScheduleAccepted);
    connect(reserveSeatsWindow, &ReserveSeatsWindow::seatsAccepted, this, &BookTicketWindow::onSeatsAccepted);
    connect(inputPersonalDataWindow, &InputPersonalDataWindow::personalDataAccepted, this, &BookTicketWindow::onPersonalDataAccepted);
    connect(selectScheduleWindow, &SelectScheduleWindow::scheduleSelected, reserveSeatsWindow, &ReserveSeatsWindow::initializeSeatsAfterSchedule);
}

void BookTicketWindow::onMovieAccepted(int movieID) {
    this->movieID = movieID;
    Movie movie = movieDatabase.getMovieById(movieID);
    inputPersonalDataWindow->setMovie(movie);
}

void BookTicketWindow::onScheduleAccepted(int scheduleID) {
    this->scheduleID = scheduleID;
    Schedule schedule = scheduleDatabase.getScheduleById(scheduleID);
    inputPersonalDataWindow->setDateTime(schedule.getDateTime());
}

void BookTicketWindow::onSeatsAccepted(std::vector<Seat*> seats) {
    this->seats = seats;
    inputPersonalDataWindow->setSeat(seats.size());
}

void BookTicketWindow::onPersonalDataAccepted(QString name, QString surname, QString email) {
    this->name = name;
    this->surname = surname;
    this->email = email;

    for (Seat* seat : seats) {
        Booking booking(movieID, scheduleID, seat->getSeatNumber(), name, surname, email); 
        if (!bookingDatabase.addBooking(booking)) {
            QMessageBox::critical(nullptr, "Booking Error", "Failed to add booking to database!");
            return;
        }
    }

    selectMovieWindow->resetSelectedMovieId();
    reserveSeatsWindow->resetReservedSeats();
    inputPersonalDataWindow->resetInputs();
}
