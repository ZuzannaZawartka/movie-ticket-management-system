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
    bool updateSchedule(const Schedule& oldSchedule, const Schedule& newSchedule);
    Schedule getScheduleById(int id);
private:
    MovieDatabase movieDatabase;
};