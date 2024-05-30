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

int BookingDatabase::getBookingId(const Booking& booking)
{
    QString queryStr = "SELECT id FROM Booking WHERE "
        "movieId = :movieId AND "
        "scheduleId = :scheduleId AND "
        "seat = :seat AND "
        "name = :name AND "
        "surname = :surname AND "
        "email = :email;";
    QVariantList values;
    values << booking.getMovieId() << booking.getScheduleId() << booking.getSeat()
        << booking.getName() << booking.getSurname() << booking.getEmail();

    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve booking ID!");
        return -1;
    }

    if (query.next()) {
        return query.value(0).toInt(); // get the first column of the first row
    }
    else {
        QMessageBox::critical(nullptr, "Database Error", "Booking not found!");
        return -1;
    }
}
Booking BookingDatabase::getBookingById(int id)
{
    QString queryStr = "SELECT * FROM Booking WHERE id = :id;";
    QVariantList values;
    values << id;

    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve booking by ID!");
        return Booking(-1, -1, "", "", "", ""); // return empty booking object
    }

    if (query.next()) {
        int movieId = query.value("movieId").toInt();
        int scheduleId = query.value("scheduleId").toInt();
        QString seat = query.value("seat").toString();
        QString name = query.value("name").toString();
        QString surname = query.value("surname").toString();
        QString email = query.value("email").toString();

        return Booking(movieId, scheduleId, seat, name, surname, email);
    }
    else {
        return Booking(-1, -1, "", "", "", ""); // return empty booking object
    }
}

bool BookingDatabase::updateBooking(const Booking& oldBooking, const Booking& newBooking)
{
    // check if the old booking exists
    int bookingId = getBookingId(oldBooking);
    if (bookingId == -1) {
        QMessageBox::critical(nullptr, "Database Error", "Old booking not found.");
        return false;
    }

    // check if the new booking already exists
    if (bookingExists(newBooking)) {
        QMessageBox::critical(nullptr, "Database Error", "New booking already exists.");
        return false;
    }

    QString queryStr = "UPDATE Booking SET "
        "movieId = :newMovieId, "
        "scheduleId = :newScheduleId, "
        "seat = :newSeat, "
        "name = :newName, "
        "surname = :newSurname, "
        "email = :newEmail "
        "WHERE id = :id;";
    QVariantList values;
    values << newBooking.getMovieId() << newBooking.getScheduleId() << newBooking.getSeat()
        << newBooking.getName() << newBooking.getSurname() << newBooking.getEmail() << bookingId;

    return executeQuery(queryStr, values);
}
void BookingDatabase::removeInvalidBookings() {
    QList<Booking> allBookings = getAllBookings();

    for (const Booking& booking : allBookings) {
        Schedule schedule = scheduleDatabase.getScheduleById(booking.getScheduleId());
        if (scheduleDatabase.getScheduleId(schedule) == -1) { 
            deleteBooking(booking);
        }
    }
}