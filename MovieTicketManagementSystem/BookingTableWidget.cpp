#include "BookingTableWidget.h"
#include <QStandardItem>


BookingTableWidget::BookingTableWidget(QTableWidget* tableWidget)
    : tableWidget(tableWidget)

{
    tableWidget->setColumnCount(6);

    tableWidget->setHorizontalHeaderLabels({ "Title", "Time/Date", "Name", "Surname", "E-mail", "Seat"});

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); // select entire row
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // turn off editing


    setBookingsInTableWidget();
}

BookingTableWidget::~BookingTableWidget()
{
}

void BookingTableWidget::setBookingsInTableWidget()
{

    tableWidget->clearContents();

    // download all bookings from database
    QList<Booking> bookings = bookingDatabase.getAllBookings();

    // set number of rows in QTableWidget to the number of bookings
    tableWidget->setRowCount(bookings.size());

    for (int row = 0; row < bookings.size(); ++row) {
        Booking booking = bookings[row];

        Movie movie = movieDatabase.getMovieById(booking.getMovieId());
        Schedule schedule = scheduleDatabase.getScheduleById(booking.getScheduleId());

        QDateTime dateTime = schedule.getDateTime();
        QString dateTimeString = dateTime.toString();

        QTableWidgetItem* titleItem = new QTableWidgetItem(movie.getTitle());
        QTableWidgetItem* dateItem = new QTableWidgetItem(dateTimeString);
        QTableWidgetItem* nameItem = new QTableWidgetItem(booking.getName());
        QTableWidgetItem* surnameItem = new QTableWidgetItem(booking.getSurname());
        QTableWidgetItem* emailItem = new QTableWidgetItem(booking.getEmail());
        QTableWidgetItem* seatItem = new QTableWidgetItem(booking.getSeat());

        tableWidget->setItem(row, 0, titleItem);
        tableWidget->setItem(row, 1, dateItem);
        tableWidget->setItem(row, 2, nameItem);
        tableWidget->setItem(row, 3, surnameItem);
        tableWidget->setItem(row, 4, emailItem);
        tableWidget->setItem(row, 5, seatItem);
    }

    tableWidget->resizeColumnsToContents();
}

QTableWidget* BookingTableWidget::getTableWidget() const
{
    return tableWidget;
}
