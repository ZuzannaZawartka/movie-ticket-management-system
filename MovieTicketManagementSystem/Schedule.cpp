#include "Schedule.h"

Schedule::Schedule(const Movie& movie, const QDate& date, const QTime& time, int durationMinutes)
    : movie(movie), date(date), time(time), durationMinutes(durationMinutes)
{
}

const Movie& Schedule::getMovie() const
{
    return movie;
}

QDate Schedule::getDate() const
{
    return date;
}

QTime Schedule::getTime() const
{
    return time;
}

int Schedule::getDurationMinutes() const
{
    return durationMinutes;
}