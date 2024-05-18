#pragma once
#include "Movie.h"
#include <QDate>
#include <QTime>

class Schedule
{
public:
    Schedule(int movieId, const QDate& date, const QTime& time, int durationMinutes);

    int getMovieId() const;
    QDate getDate() const;
    QTime getTime() const;
    int getDurationMinutes() const;

private:
    int movieId;
    QDate date;
    QTime time;
    int durationMinutes;
};
