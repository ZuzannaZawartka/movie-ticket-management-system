#include "Booking.h"

Booking::Booking(int movieId, int scheduleId, QString seat, QString name, QString surname, QString email)
{
	this->movieId = movieId;
	this->scheduleId = scheduleId;
	this->seat = seat;
	this->name = name;
	this->surname = surname;
	this->email = email;
}

int Booking::getMovieId() const
{
	return movieId;
}

int Booking::getScheduleId() const
{
	return scheduleId;
}

QString Booking::getSeat() const
{
	return seat;
}

QString Booking::getName() const
{
	return name;
}

QString Booking::getSurname() const
{
	return surname;
}

QString Booking::getEmail() const
{
	return email;
}
