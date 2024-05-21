#pragma once

#include <QString>
#include <QVariantList>
#include <QSqlQuery>
#include <QMessageBox>
#include "Booking.h"
#include "DatabaseManager.h"

class BookingDatabase : public DatabaseManager
{
public:
    BookingDatabase();

    bool createTable();
    bool addBooking(const Booking& booking);
    bool deleteBooking(const Booking& booking);
    bool bookingExists(const Booking& booking);
    QList<Booking> getAllBookings();


private:
};
