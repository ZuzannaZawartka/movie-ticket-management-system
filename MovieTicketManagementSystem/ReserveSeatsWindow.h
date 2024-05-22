#pragma once

#include <QGridLayout>
#include <QObject>
#include <QString>
#include <QPushButton>
#include "Seat.h"
#include "BookingDatabase.h"

class ReserveSeatsWindow : public QObject
{
    Q_OBJECT

public:
    ReserveSeatsWindow(QGridLayout* layout, QPushButton* acceptButton);
    ~ReserveSeatsWindow();
    std::vector<Seat*> getReservedSeats() const;
    bool isSeatReserved();
    void resetReservedSeatsWindow();
    

signals:
    void seatsAccepted(std::vector<Seat*> seats);

private:
    void generateSeats();
    void loadSeatData();
    void resetReservedSeats();
    void onButtonClicked(QString seatNumber);
    void clearSeats();
    void refreshSeats();
    Seat* findSeatByNumber(const QString& seatNumber);
    void setOccupiedSeats();

    QPushButton* acceptButton;
    QGridLayout* layout;
    QString fileName;
    std::vector<Seat*> seats;      // To store seat pointers
    std::vector<QString> seatData; // To store seat data from the file

    BookingDatabase bookingDatabase;

private slots:
    void onAcceptButtonClicked();  // Slot to handle accept button click
};