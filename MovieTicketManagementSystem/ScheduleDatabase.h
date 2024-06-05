#pragma once
#include "DatabaseManager.h"
#include "Schedule.h"
#include "MovieDatabase.h"
#include <QStringList>
#include <QVariantList>
#include <QSqlQuery>
#include <QSqlRecord>

class ScheduleDatabase : public DatabaseManager
{
public:
    ScheduleDatabase();

    bool createScheduleTable();
    bool addSchedule(const Schedule& schedule);
    bool deleteSchedule(const Schedule& schedule);
    int getScheduleId(const Schedule& schedule);
    QList<Schedule> getAllSchedules();
    bool isTableExists();
    void removeInvalidSchedules();
    bool isScheduleExists(const Schedule& schedule);
    bool updateSchedule(const Schedule& oldSchedule, const Schedule& newSchedule);
    Schedule getScheduleByMovieAndDateTime(int movieId, const QDateTime& dateTime);
    Schedule getScheduleById(int id);
    QList<Schedule> getSchedulesByMovieIdSortedByDate(int movieId);
    QList<Schedule> getSchedulesByMovieId(int movieId);

private:
    MovieDatabase movieDatabase;
};