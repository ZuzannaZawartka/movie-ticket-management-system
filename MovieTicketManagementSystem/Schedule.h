#pragma once
#include "Movie.h"
#include <QDate>
#include <QTime>

class Schedule
{
public:
    Schedule(const Movie& movie, const QDate& date, const QTime& time, int durationMinutes);

    const Movie& getMovie() const;
    QDate getDate() const;
    QTime getTime() const;
    int getDurationMinutes() const;

private:
    const Movie& movie;
    QDate date;
    QTime time;
    int durationMinutes;
};
