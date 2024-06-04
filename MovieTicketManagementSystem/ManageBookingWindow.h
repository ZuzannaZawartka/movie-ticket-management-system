#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "BookingDatabase.h"
#include "ScheduleDatabase.h"
#include "MovieDatabase.h"
#include "BookingTableWidget.h"

class ManageBookingWindow : public QWidget
{
    Q_OBJECT;

public:
    explicit ManageBookingWindow(QComboBox* titleEdit, QComboBox* dateTimeEdit,  QLineEdit* name, QLineEdit* surname, QLineEdit* Email, QLineEdit* seat, QPushButton* removeButton, QPushButton* editButton, QTableWidget* bookingTableWidget);
    ~ManageBookingWindow();

private:
    QComboBox* titleEdit;
    QComboBox* dateTimeEdit;
    QLineEdit* name;
    QLineEdit* surname;
    QLineEdit* Email; 
    QLineEdit* seat;
    QPushButton* removeButton;
    QPushButton* editButton;
    BookingTableWidget* bookingTableWidget;
    int selectedBookingId;

    BookingDatabase bookingDatabase;
    MovieDatabase movieDatabase;
    ScheduleDatabase scheduleDatabase;

    bool checkInputFields();
    void updateFields();
    void updateFields(const Booking& Booking);
    Booking getBookingFromFields();

public slots:
    void refreshBookings();

private slots:
    void removeCurrentBooking();
    void editCurrentBooking();
    void onTitleChanged();
    void onBookingSelected(const QModelIndex& index);
};