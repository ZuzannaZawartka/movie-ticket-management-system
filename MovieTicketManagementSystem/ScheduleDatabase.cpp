#include "ScheduleDatabase.h"
#include "MovieDatabase.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>


ScheduleDatabase::ScheduleDatabase() {
  
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
    try {
        
        int movieId = schedule.getMovieId();

        // Check if movie exists in movieDatabase
        if (!movieDatabase.movieExists(movieDatabase.getMovieById(movieId))) {
            QMessageBox::critical(nullptr, "Database Error", "Movie does not exist!");
            return false;
        }
        int duration = movieDatabase.getMovieById(movieId).getDuration();
        // Check if schedule already exists in scheduleDatabase

        if (isScheduleExists(schedule)) {
            QMessageBox::critical(nullptr, "Database Error", "Schedule already exists!");
            return false;
        }

        QString query = "INSERT INTO schedule (movieId, date, time, duration) "
            "VALUES (?, ?, ?, ?);";

        QVariantList values;
        values << movieId << schedule.getDate().toString("yyyy-MM-dd")
            << schedule.getTime().toString("hh:mm:ss") << duration;

        return executeQuery(query, values);
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Database Error", QString("Error: ") + e.what());
        return false;
    }
}

bool ScheduleDatabase::deleteSchedule(const Schedule& schedule)
{
    int scheduleId = getScheduleId(schedule);

    if (scheduleId == -1) {
        QMessageBox::critical(nullptr, "Database Error", "Schedule not found!");
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
    QString queryStr = "SELECT id FROM schedule WHERE movieId = :movieId AND date = :date AND time = :time;";
    QVariantList values;
    values << schedule.getMovieId() << schedule.getDate().toString("yyyy-MM-dd") << schedule.getTime().toString("hh:mm:ss");

    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve schedule ID!");
        return -1;
    }

    if (query.next()) {
        return query.value(0).toInt();
    }
    else {
        return -1;
    }
}
QList<Schedule> ScheduleDatabase::getAllSchedules()
{
    QList<Schedule> schedules;

    try {
        QString queryStr = "SELECT * FROM schedule ORDER BY date ASC, time ASC;";  
        QSqlQuery query = prepareQueryWithBindings(queryStr);

        if (!query.exec()) {
            throw std::runtime_error("Failed to execute query to retrieve schedules.");
        }

        while (query.next()) {
            int movieId = query.value("movieId").toInt();
            try {
                QDate date = query.value("date").toDate();
                QTime time = query.value("time").toTime();
                int durationMinutes = query.value("duration").toInt();

                Schedule schedule(movieId, date, time, durationMinutes);
                schedules.append(schedule);
            }
            catch (const std::exception& e) {
                // Obs³uga przypadku, gdy film nie istnieje
                QString errorMessage = QString("Error retrieving movie with ID %1: %2").arg(movieId).arg(e.what());
                QMessageBox::critical(nullptr, "Database Error", errorMessage);

                continue; // Pomiñ ten harmonogram, jeœli film nie istnieje
            }
        }
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Database Error", QString("Error in getAllSchedules: ") + e.what());
        return schedules;
    }

    return schedules;
}
bool ScheduleDatabase::isScheduleExists(const Schedule& schedule)
{
    QString queryStr = "SELECT COUNT(*) FROM schedule WHERE movieId = :movieId AND date = :date AND time = :time AND duration = :duration;";
    QVariantList values;
    values << schedule.getMovieId() << schedule.getDate().toString("yyyy-MM-dd")
        << schedule.getTime().toString("hh:mm:ss") << schedule.getDurationMinutes();

    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to check if schedule exists!");
        return false;
    }

    query.next();
    int count = query.value(0).toInt(); //how many rows have been found

    return count != 0;
}

Schedule ScheduleDatabase::getScheduleById(int id)
{
    QString queryStr = "SELECT * FROM schedule WHERE id = :id;";
    QVariantList values;
    values << id;

    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve schedule by ID!");

    }

    if (query.next()) {
        int movieId = query.value("movieId").toInt();
        QDate date = query.value("date").toDate();
        QTime time = query.value("time").toTime();
        int durationMinutes = query.value("duration").toInt();

        return Schedule(movieId, date, time, durationMinutes);
    }
    
}

QList<Schedule> ScheduleDatabase::getSchedulesByMovieIdSortedByDate(int movieId)
{
    QList<Schedule> schedules;
    QString queryStr = "SELECT * FROM schedule WHERE movieId = :movieId ORDER BY date ASC, time ASC;";
    QVariantList values;
    values << movieId;

    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve schedules for movie ID " + QString::number(movieId));
        return schedules;
    }

    while (query.next()) {
        QDate date = query.value("date").toDate();
        QTime time = query.value("time").toTime();
        int durationMinutes = query.value("duration").toInt();

        Schedule schedule(movieId, date, time, durationMinutes);
        schedules.append(schedule);
    }

    return schedules;
}



bool ScheduleDatabase::updateSchedule(const Schedule& oldSchedule, const Schedule& newSchedule)
{
    // SprawdŸ, czy stary harmonogram istnieje
    int scheduleId = getScheduleId(oldSchedule);
    if (scheduleId == -1) {
        QMessageBox::critical(nullptr, "Database Error", "Old schedule not found.");
        return false;
    }

    // SprawdŸ, czy nowy harmonogram nie istnieje ju¿ w bazie danych
    if (getScheduleId(newSchedule) != -1) {
        QMessageBox::critical(nullptr, "Database Error", "New schedule already exists.");
        return false;
    }

    QString queryStr = "UPDATE schedule SET movieId = :newMovieId, date = :newDate, time = :newTime, duration = :newDuration WHERE id = :id;";
    QVariantList values;
    values << newSchedule.getMovieId() << newSchedule.getDate().toString("yyyy-MM-dd")
        << newSchedule.getTime().toString("hh:mm:ss") << newSchedule.getDurationMinutes() << scheduleId;

    return executeQuery(queryStr, values);
}
void ScheduleDatabase::removeInvalidSchedules()
{
    QString queryStr = "SELECT * FROM schedule;";
    QSqlQuery query = prepareQueryWithBindings(queryStr);

    if (!query.exec()) {
        throw std::runtime_error("Failed to execute query to retrieve schedules.");
    }

    while (query.next()) {
        int movieId = query.value("movieId").toInt();
        if (!movieDatabase.movieExists(movieDatabase.getMovieById(movieId))) {
            QString deleteQueryStr = "DELETE FROM schedule WHERE movieId = ?;";
            QSqlQuery deleteQuery;
            deleteQuery.prepare(deleteQueryStr);
            deleteQuery.addBindValue(movieId);

            if (!deleteQuery.exec()) {
                QString errorMessage = QString("Failed to delete invalid schedule for movie ID %1").arg(movieId);
                QMessageBox::critical(nullptr, "Database Error", errorMessage);
                
            }
            
        }
    }
}
Schedule ScheduleDatabase::getScheduleByMovieAndDateTime(int movieId, const QDateTime& dateTime)
{
    QString queryStr = "SELECT * FROM Schedule WHERE movieId = ? AND date = ? AND time = ?";

    QSqlQuery query;
    query.prepare(queryStr);
    query.addBindValue(movieId);
    query.addBindValue(dateTime.date().toString("yyyy-MM-dd"));
    query.addBindValue(dateTime.time().toString("hh:mm:ss")); 
    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve schedule by movie and date time!");
        return Schedule(-1, QDate(), QTime(), -1);
    }

    if (query.next()) {
        int movieId = query.value("movieId").toInt();
        QDate date = query.value("date").toDate();
        QTime time = query.value("time").toTime();
        int durationMinutes = query.value("durationMinutes").toInt();

        return Schedule(movieId, date, time, durationMinutes);
    }
    
}