#pragma once

#include <QGridLayout>
#include <QObject>
#include <QString>
#include <QPushButton>
#include "Seat.h"

class ReserveSeatsWindow : public QObject
{
    Q_OBJECT

public:
    ReserveSeatsWindow(QGridLayout* layout, QPushButton* acceptButton);
    ~ReserveSeatsWindow();
    std::vector<QString> getReservedSeats() const;
    bool isSeatReserved();
    void selectAllSeats();

signals:
    void seatsAccepted(std::vector<Seat*> seats);

private:
    void generateSeats();
    void loadSeatData();
    void resetReservedSeats();
    void onButtonClicked(int row, int col);
    void clearSeats();
    void refreshSeats();

    QPushButton* acceptButton;
    QGridLayout* layout;
    QString fileName;
    std::vector<QString> reservedSeats;
    std::vector<QString> seatData; // To store seat data from the file
    std::vector<Seat*> seats;      // To store seat pointers

private slots:
    void onAcceptButtonClicked();  // Slot to handle accept button click
};