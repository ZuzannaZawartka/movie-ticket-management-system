#include "BookTicketWindow.h"
#include "SelectMovieWindow.h"
#include "SelectScheduleWindow.h"

BookTicketWindow::BookTicketWindow(SelectMovieWindow* selectMovieWindow, SelectScheduleWindow* selectScheduleWindow) : selectMovieWindow(selectMovieWindow), selectScheduleWindow(selectScheduleWindow)
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
