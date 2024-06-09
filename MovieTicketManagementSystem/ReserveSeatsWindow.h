#pragma once
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include "Seat.h"
#include "BookingDatabase.h"

class ReserveSeatsWindow : public QObject
{
    Q_OBJECT

public:
    ReserveSeatsWindow(QGridLayout* layout, QPushButton* acceptButton);
    ~ReserveSeatsWindow();
    bool isSeatReserved();
    void resetReservedSeats();
    void reloadSeatData();
    std::vector<Seat*> getReservedSeats() const;

public slots:
    void initializeSeatsAfterSchedule(int ScheduleId);// Slot to initialize seats

signals:
    void seatsAccepted(std::vector<Seat*> seats);// Signal to send reserved seats

private:
    void generateSeats();
    void loadSeatData();
    void onButtonClicked(QString seatNumber);
    void setOccupiedSeats(int scheduleID);
    Seat* findSeatByNumber(const QString& seatNumber);
    QPushButton* acceptButton;
    QGridLayout* layout;
    QString fileName;
    std::vector<Seat*> seats;      // To store seat pointers
    std::vector<QString> seatData; // To store seat data from the file
    BookingDatabase bookingDatabase;

private slots:
    void onAcceptButtonClicked();  // Slot to handle accept button click
};