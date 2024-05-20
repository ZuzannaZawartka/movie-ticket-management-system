#pragma once
#include "Seat.h"
#include "SelectMovieWindow.h"
#include "SelectScheduleWindow.h"
#include "ReserveSeatsWindow.h"

class BookTicketWindow
{
public:
	BookTicketWindow(SelectMovieWindow* selectMovieWindow,SelectScheduleWindow* selectScheduleWindow, ReserveSeatsWindow* reserveSeatsWindow);
	~BookTicketWindow();

private:
	SelectMovieWindow* selectMovieWindow;
	SelectScheduleWindow* selectScheduleWindow;
	ReserveSeatsWindow* reserveSeatsWindow;

	// Variables to hold the ID of the selected movie, schedule and seat
	int movieID;
	int scheduleID;

	std::vector<Seat*> seats; // Container to hold seat objects

	QString name;
	QString surname;
	QString email;


};

