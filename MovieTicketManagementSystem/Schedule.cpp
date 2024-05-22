#include "Schedule.h"
#include "Movie.h"

Schedule::Schedule(int movieId, const QDate& date, const QTime& time, int durationMinutes)
    : movieId(movieId), date(date), time(time), durationMinutes(durationMinutes)
{
}

int Schedule::getMovieId() const
{
    return movieId;
}

QDate Schedule::getDate() const
{
    return date;
}

QTime Schedule::getTime() const
{
    return time;
}

QDateTime Schedule::getDateTime() const
{
    return QDateTime(date, time);
}


int Schedule::getDurationMinutes() const
{
    return durationMinutes;
}
