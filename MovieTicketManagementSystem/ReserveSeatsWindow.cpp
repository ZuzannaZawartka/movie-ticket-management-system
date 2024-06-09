#include "ReserveSeatsWindow.h"
#include <QFile>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include "Seat.h"

ReserveSeatsWindow::ReserveSeatsWindow(QGridLayout* layout, QPushButton* acceptButton)
    : layout(layout), acceptButton(acceptButton) {
    fileName = "numbers.txt";
    loadSeatData();
    generateSeats();
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(onAcceptButtonClicked()));
}

ReserveSeatsWindow::~ReserveSeatsWindow() {
    for (Seat* seat : seats) {
        delete seat;
    }
    delete layout;
}

void ReserveSeatsWindow::loadSeatData() {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Could not open file");
        return;
    }

    QTextStream in(&file);
    seatData.clear();

    while (!in.atEnd()) {
        QString line = in.readLine();
        seatData.push_back(line);
    }

    file.close();
}

Seat* ReserveSeatsWindow::findSeatByNumber(const QString& seatNumber) {
    for (Seat* seat : seats) {
        if (seat->getSeatNumber() == seatNumber) {
            return seat;
        }
    }
    return nullptr;
}

void ReserveSeatsWindow::generateSeats() {
    int numRows = seatData.size();

    for (int row = 0; row < numRows; ++row) {
        QString line = seatData[row];
        int numCols = line.size();
        for (int col = numCols - 1; col >= 0; --col) {
            QChar number = line[col];
            Seat* seat = new Seat(row, col, number);
            seats.push_back(seat);
            connect(seat, &Seat::clicked, this, &ReserveSeatsWindow::onButtonClicked);
            layout->addWidget(seat->getButton(), row + 1, numCols - col); 
        }

        QLabel* rowLabel = new QLabel(QString(QChar('A' + row)));
        layout->addWidget(rowLabel, row + 1, 0);
    }
}


void ReserveSeatsWindow::onButtonClicked(QString seatNumber) {
    Seat* seat = findSeatByNumber(seatNumber);
    if (seat) {
		seat->chooseSeat();
	}
}


std::vector<Seat*> ReserveSeatsWindow::getReservedSeats() const {
    std::vector<Seat*> selectedSeats;
    for (Seat* seat : seats) {
        if (seat->isSelectedSeat()) {
            selectedSeats.push_back(seat);
        }
    }
    return selectedSeats;
}

bool ReserveSeatsWindow::isSeatReserved() {
    for (Seat* seat : seats) {
        if (seat->isSelectedSeat()) {
            return true;
        }
    }
    return false;
}


void ReserveSeatsWindow::resetReservedSeats() {
    for (Seat* seat : seats) {
        seat->resetSeat();
    }
}

void ReserveSeatsWindow::reloadSeatData() {
    for (Seat* seat : seats) {
        delete seat;
    }
    seats.clear();
    seatData.clear();

    loadSeatData();
    generateSeats();

    bookingDatabase.deleteAllBookings();
}

void ReserveSeatsWindow::setOccupiedSeats(int scheduleID) {
    QList<QString> occupiedSeatNumbers = bookingDatabase.getOccupiedSeats(scheduleID);
    for (const QString& seatNumber : occupiedSeatNumbers) {
        Seat* seat = findSeatByNumber(seatNumber);
        if (seat) {
            seat->setEnabled(false);
        }
    }
}

void ReserveSeatsWindow::initializeSeatsAfterSchedule(int scheduleID) {
    resetReservedSeats();
    setOccupiedSeats(scheduleID);
}

void ReserveSeatsWindow::onAcceptButtonClicked() {
    if (!isSeatReserved()) {
        QMessageBox::information(nullptr, "Error", "You need to select at least one seat.");
    }
    else {
        emit seatsAccepted(getReservedSeats());
    }
}
