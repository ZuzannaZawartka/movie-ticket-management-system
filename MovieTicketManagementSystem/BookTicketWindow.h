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

private:
	SelectMovieWindow* selectMovieWindow;
	SelectScheduleWindow* selectScheduleWindow;
	ReserveSeatsWindow* reserveSeatsWindow;
	InputPersonalDataWindow* inputPersonalDataWindow;
	BookingDatabase bookingDatabase;
	MovieDatabase movieDatabase;
	ScheduleDatabase scheduleDatabase;
	std::vector<Seat*> seats;
	QString name;
	QString surname;
	QString email;
	int movieID;
	int scheduleID;

private slots:
	void onMovieAccepted(int movieID);
	void onScheduleAccepted(int scheduleID);
	void onSeatsAccepted(std::vector<Seat*> seats);
	void onPersonalDataAccepted(QString name, QString surname, QString email);
};

