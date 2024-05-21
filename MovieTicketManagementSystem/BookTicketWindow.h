#pragma once
#include "Seat.h"
#include "SelectMovieWindow.h"
#include "SelectScheduleWindow.h"
#include "ReserveSeatsWindow.h"
#include "InputPersonalDataWindow.h"
#include "BookingDatabase.h"


class BookTicketWindow: public QObject
{
	Q_OBJECT
public:
	BookTicketWindow(SelectMovieWindow* selectMovieWindow,SelectScheduleWindow* selectScheduleWindow, ReserveSeatsWindow* reserveSeatsWindow,InputPersonalDataWindow* inputPersonalDataWindow);
	~BookTicketWindow();

private:
	SelectMovieWindow* selectMovieWindow;
	SelectScheduleWindow* selectScheduleWindow;
	ReserveSeatsWindow* reserveSeatsWindow;
	InputPersonalDataWindow* inputPersonalDataWindow;
	BookingDatabase bookingDatabase;
	// Variables to hold the ID of the selected movie, schedule and seat
	int movieID;
	int scheduleID;

	std::vector<Seat*> seats; // Container to hold seat objects

	QString name;
	QString surname;
	QString email;

private slots:

	void onMovieAccepted(int movieID);
	void onScheduleAccepted(int scheduleID);
	void onSeatsAccepted(std::vector<Seat*> seats);
	void onPersonalDataAccepted(QString name, QString surname, QString email);

};

