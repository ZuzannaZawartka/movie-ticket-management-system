#pragma once
#include <QString>
#include "MovieDatabase.h"
#include "ScheduleDatabase.h"

class Booking
{

public:
	Booking(int movieId, int scheduleId, QString seat, QString name, QString surname, QString email);
	int getMovieId() const;
	int getScheduleId() const;
	QString getSeat() const;
	QString getName() const;
	QString getSurname() const;
	QString getEmail() const;

private:
	int movieId;
	int scheduleId;
	QString seat;
	QString name;
	QString surname;
	QString email;
};

