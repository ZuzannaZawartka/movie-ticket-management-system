#include "ScheduleDatabase.h"
#include "MovieDatabase.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <iostream>

using namespace std;

const QString DatabasePath = "database.db";


ScheduleDatabase::ScheduleDatabase()  {
    createScheduleTable();
}


bool ScheduleDatabase::createScheduleTable()
{
    QString query = "CREATE TABLE IF NOT EXISTS schedule ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "movieId INTEGER, "
        "date TEXT, "
        "time TEXT, "
        "duration INTEGER"
        ")";

    return executeQuery(query, QVariantList());
}

bool ScheduleDatabase::addSchedule(const Schedule& schedule)
{
    QString query = "INSERT INTO schedule (movieId, date, time, duration) "
        "VALUES (?, ?, ?, ?);";

    QVariantList values;
    values << movieDatabase.getMovieId(schedule.getMovie()) << schedule.getDate().toString("yyyy-MM-dd")
        << schedule.getTime().toString("hh:mm:ss") << schedule.getDurationMinutes();

    return executeQuery(query, values);
}

bool ScheduleDatabase::deleteSchedule(const Schedule& schedule)
{
    int scheduleId = getScheduleId(schedule);

    if (scheduleId == -1) {
        cout << "Schedule not found." << endl;
        return false;
    }

    QString query = "DELETE FROM schedule WHERE id = :id;"; 

    QVariantList values;
    values << scheduleId;

    return executeQuery(query, values);
}

bool ScheduleDatabase::isTableExists()
{
    QString query = "SELECT 1 FROM schedule LIMIT 1;";
    return executeQuery(query, QVariantList());
}

int ScheduleDatabase::getScheduleId(const Schedule& schedule)
{
    QString queryStr = "SELECT id FROM schedule WHERE movie = :movie AND date = :date AND time = :time;";
    QVariantList values;
    values << schedule.getMovie().getTitle() << schedule.getDate().toString("yyyy-MM-dd") << schedule.getTime().toString("hh:mm:ss");

    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve schedule ID!");
        return -1;
    }

    if (query.next()) {
        return query.value(0).toInt(); 
    }
    else {
        QMessageBox::critical(nullptr, "Database Error", "Schedule not found!");
        return -1;
    }
}

QList<Schedule> ScheduleDatabase::getAllSchedules()
{
    try {
        QList<Schedule> schedules;

        QString queryStr = "SELECT * FROM schedule;";

        QSqlQuery query = prepareQueryWithBindings(queryStr);

        if (!query.exec()) {
            QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve schedules!");
            return schedules;
        }

        while (query.next()) {
            int movieId = query.value("movieId").toInt(); 
            Movie movie = movieDatabase.getMovieById(movieId);
            QDate date = query.value("date").toDate();
            QTime time = query.value("time").toTime();
            int durationMinutes = query.value("duration").toInt(); 

            Schedule schedule(movie, date, time, durationMinutes);

            schedules.append(schedule);
        }

        return schedules;
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Database Error", QString("Error: ") + e.what());
        return QList<Schedule>(); 
    }
}