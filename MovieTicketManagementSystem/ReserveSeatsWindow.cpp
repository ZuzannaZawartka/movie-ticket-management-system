#include "ReserveSeatsWindow.h"
#include <QFile>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include "Seat.h"

ReserveSeatsWindow::ReserveSeatsWindow(QGridLayout* layout, QPushButton* acceptButton)
    : layout(layout), acceptButton(acceptButton)
{
    fileName = "numbers.txt";
    loadSeatData();
    generateSeats();

    connect(acceptButton, SIGNAL(clicked()), this, SLOT(onAcceptButtonClicked()));
}

ReserveSeatsWindow::~ReserveSeatsWindow()
{
    for (Seat* seat : seats) {
        delete seat;
    }
    delete layout;
}

void ReserveSeatsWindow::loadSeatData()
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Could not open file");
        return;
    }

    QTextStream in(&file);
    seatData.clear(); // Clear existing data

    while (!in.atEnd()) {
        QString line = in.readLine();
        seatData.push_back(line);
    }

    file.close();
}

void ReserveSeatsWindow::generateSeats()
{
    for (int row = 0; row < seatData.size(); ++row) {
        QString line = seatData[row];
        for (int col = 0; col < line.size(); ++col) {
            QChar number = line[col]; // type of seat (0 - free, 1 - special, 2 - vip)
            Seat* seat = new Seat(row, col, number); // create seat object

            seats.push_back(seat); // add to vector of seats

            connect(seat, &Seat::clicked, this, &ReserveSeatsWindow::onButtonClicked);
            layout->addWidget(seat->getButton(), row + 1, col + 1); // add button to layout
        }

        // add label with row letter
        QLabel* rowLabel = new QLabel(QString(QChar('A' + row)));
        layout->addWidget(rowLabel, row + 1, 0);
    }
}

void ReserveSeatsWindow::clearSeats()
{
    for (Seat* seat : seats) {
        layout->removeWidget(seat->getButton());
        delete seat;
    }
    seats.clear();
}

void ReserveSeatsWindow::refreshSeats()
{
    clearSeats();
    loadSeatData();
    generateSeats();
}

void ReserveSeatsWindow::onButtonClicked(int row, int col)
{
    QString seatNumber = QString(QChar('A' + row)) + QString::number(col + 1);

    // check if seat is reserved
    if (std::find(reservedSeats.begin(), reservedSeats.end(), seatNumber) != reservedSeats.end()) {
        // remove seat from reservedSeats
        reservedSeats.erase(std::remove(reservedSeats.begin(), reservedSeats.end(), seatNumber), reservedSeats.end());

        // QMessageBox::information(nullptr, "Seat Clicked", QString("Seat %1 unclicked").arg(seatNumber));
    }
    else {
        // add seat to reservedSeats
        reservedSeats.push_back(seatNumber);

        // QMessageBox::information(nullptr, "Seat Clicked", QString("Seat %1 clicked").arg(seatNumber));
    }
}

std::vector<QString> ReserveSeatsWindow::getReservedSeats() const
{
    return reservedSeats;
}

bool ReserveSeatsWindow::isSeatReserved()
{
    return !reservedSeats.empty();
}

void ReserveSeatsWindow::resetReservedSeats()
{
    reservedSeats.clear();
}

void ReserveSeatsWindow::selectAllSeats()
{
    for (Seat* seat : seats) {
        seat->chooseSeat();
    }
}

void ReserveSeatsWindow::onAcceptButtonClicked()
{
    if (reservedSeats.empty()) {
        QMessageBox::information(nullptr, "Error", "You need to reserve at least one seat.");
    }
    else {
        QMessageBox::information(nullptr, "Success", "Seats reserved successfully.");
        resetReservedSeats(); // reset the reserved seats after confirming
    }
}
