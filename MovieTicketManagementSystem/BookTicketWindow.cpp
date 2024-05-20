#include "BookTicketWindow.h"
#include "SelectMovieWindow.h"
#include "SelectScheduleWindow.h"
#include "ReserveSeatsWindow.h"

BookTicketWindow::BookTicketWindow(SelectMovieWindow* selectMovieWindow, SelectScheduleWindow* selectScheduleWindow, ReserveSeatsWindow* reserveSeatsWindow) : selectMovieWindow(selectMovieWindow), selectScheduleWindow(selectScheduleWindow), reserveSeatsWindow(reserveSeatsWindow)
{
	movieID = -1;
	scheduleID = -1;
	name = "";
	surname = "";
	email = "";

}

BookTicketWindow::~BookTicketWindow()
{

}
