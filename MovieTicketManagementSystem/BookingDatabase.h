#pragma once
#include <QString>
#include <QVariantList>
#include <QSqlQuery>
#include <QMessageBox>
#include "Booking.h"

class BookingDatabase : public DatabaseManager
{

public:
    BookingDatabase();
    bool createTable();
    bool addBooking(const Booking& booking);
    bool deleteBooking(const Booking& booking);
    bool bookingExists(const Booking& booking);
    bool deleteAllBookings();
    int getBookingId(const Booking& booking);
    Booking getBookingById(int id);
    bool updateBooking(const Booking& oldBooking, const Booking& newBooking);
    void removeInvalidBookings();
    QList<Booking> getAllBookings();
    QList<QString> getOccupiedSeats(int scheduleID);

private:
    ScheduleDatabase scheduleDatabase;
};
