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
    inputPersonalDataWindow(inputPersonalDataWindow)

{
    
    movieID = -1;
	scheduleID = -1;
    name = "";
    surname = "";
    email = "";


    // Connect signals to slots
    connect(selectMovieWindow, &SelectMovieWindow::movieSelected, this, &BookTicketWindow::onMovieAccepted);
    connect(selectScheduleWindow, &SelectScheduleWindow::scheduleSelected, this, &BookTicketWindow::onScheduleAccepted);
    connect(reserveSeatsWindow, &ReserveSeatsWindow::seatsAccepted, this, &BookTicketWindow::onSeatsAccepted);
    connect(inputPersonalDataWindow, &InputPersonalDataWindow::personalDataAccepted, this, &BookTicketWindow::onPersonalDataAccepted);


}

BookTicketWindow::~BookTicketWindow()
{
    // Destructor implementation (if needed)
}

void BookTicketWindow::onMovieAccepted(int movieID)
{
    this->movieID = movieID;
    QMessageBox::information(nullptr, "Movie Selected", QString("Movie ID: %1").arg(movieID));

    // Additional logic for handling accepted movie (if needed)
}

void BookTicketWindow::onScheduleAccepted(int scheduleID)
{
    this->scheduleID = scheduleID;

    QMessageBox::information(nullptr, "Schedule Selected", QString("Schedule ID: %1").arg(scheduleID));
    // Additional logic for handling accepted schedule (if needed)
}

void BookTicketWindow::onSeatsAccepted(std::vector<Seat*> seats)
{

    this->seats = seats;

    QMessageBox::information(nullptr, "Seats Selected", QString("Number of seats: %1").arg(seats.size()));
    // Additional logic for handling accepted seats (if needed)
}

void BookTicketWindow::onPersonalDataAccepted(QString name, QString surname, QString email)
{
    this->name = name;
    this->surname = surname;
    this->email = email;

    
    //for each seat in seats
    for (Seat* seat : seats) {
        Booking booking(movieID, scheduleID, seat->getSeatNumber(), name, surname, email); 
        if (!bookingDatabase.addBooking(booking)) {
            QMessageBox::critical(nullptr, "Booking Error", "Failed to add booking to database!");
            return;
        }
    }

    QMessageBox::information(nullptr, "Booking Success", "Booking added to database successfully!");

    // clear all data
    ///selectMovieWindow->resetSelectedMovieId();
    //selectScheduleWindow->resetSelectedScheduleId();
    //reserveSeatsWindow->resetReservedSeatsWindow();
   // inputPersonalDataWindow->resetReservedSeatsWindow();
}
