#include "BookingDatabase.h"
#include <QSqlQuery>
#include <QVariantList>
#include <QSqlRecord>
#include <QMessageBox>

BookingDatabase::BookingDatabase()
{
    createTable();
}

bool BookingDatabase::createTable() {
    QString query = "CREATE TABLE IF NOT EXISTS Booking ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "movieId INTEGER,"
        "scheduleId INTEGER,"
        "seat TEXT,"
        "name TEXT,"
        "surname TEXT,"
        "email TEXT"
        ");";

    return executeQuery(query, QVariantList());
}

bool BookingDatabase::addBooking(const Booking& booking) {
    if (bookingExists(booking)) {
        QMessageBox::critical(nullptr, "Database Error", "Booking already exists!");
        return false;
    }


    QString query = "INSERT INTO Booking (movieId, scheduleId, seat, name, surname, email) "
        "VALUES (?, ?, ?, ?, ?, ?);";
    QVariantList values;
    values << booking.getMovieId() << booking.getScheduleId() << booking.getSeat()
        << booking.getName() << booking.getSurname() << booking.getEmail();

    if (!executeQuery(query, values)) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to add booking to database!");
        return false;
    }


    return true;
}

bool BookingDatabase::deleteBooking(const Booking& booking) {
    QString query = "DELETE FROM Booking WHERE "
        "movieId = ? AND "
        "scheduleId = ? AND "
        "seat = ? AND "
        "name = ? AND "
        "surname = ? AND "
        "email = ?;";
    QVariantList values;
    values << booking.getMovieId() << booking.getScheduleId() << booking.getSeat()
        << booking.getName() << booking.getSurname() << booking.getEmail();
    return executeQuery(query, values);
}

QList<Booking> BookingDatabase::getAllBookings() {
    QList<Booking> bookings;
    QString query = "SELECT * FROM Booking;";
    QSqlQuery sqlQuery = prepareQueryWithBindings(query);

    if (!sqlQuery.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve bookings!");
        return bookings;
    }

    while (sqlQuery.next()) {
        int movieId = sqlQuery.value("movieId").toInt();
        int scheduleId = sqlQuery.value("scheduleId").toInt();
        QString seat = sqlQuery.value("seat").toString();
        QString name = sqlQuery.value("name").toString();
        QString surname = sqlQuery.value("surname").toString();
        QString email = sqlQuery.value("email").toString();
        Booking booking(movieId, scheduleId, seat, name, surname, email);
        bookings.append(booking);
    }

    return bookings;
}

bool BookingDatabase::bookingExists(const Booking& booking) {
    QString queryStr = "SELECT COUNT(*) FROM Booking WHERE "
        "movieId = ? AND "
        "scheduleId = ? AND "
        "seat = ? AND "
        "name = ? AND "
        "surname = ? AND "
        "email = ?;";
    QVariantList values;
    values << booking.getMovieId() << booking.getScheduleId() << booking.getSeat()
        << booking.getName() << booking.getSurname() << booking.getEmail();

    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to check if booking exists!");
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    return count != 0;
}


QList<QString> BookingDatabase::getOccupiedSeats(int scheduleID) {
    QList<QString> occupiedSeats;
    QString query = "SELECT DISTINCT seat FROM Booking WHERE scheduleId = :scheduleID;";
    QVariantList values;
    values << scheduleID;



    QSqlQuery sqlQuery = prepareQueryWithBindings(query, values);

    if (!sqlQuery.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve occupied seats!");
        return occupiedSeats;
    }

    while (sqlQuery.next()) {
        QString seat = sqlQuery.value("seat").toString();
        occupiedSeats.append(seat);
    }

    return occupiedSeats;
}

bool BookingDatabase::deleteAllBookings() {
    QString query = "DELETE FROM Booking;";
    return executeQuery(query, QVariantList());
}