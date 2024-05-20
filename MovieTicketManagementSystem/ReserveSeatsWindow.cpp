#include "ReserveSeatsWindow.h"
#include <QFile>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include "Seat.h"


ReserveSeatsWindow::ReserveSeatsWindow(QGridLayout* layout, QPushButton* acceptButton) : layout(layout), acceptButton(acceptButton)
{
    fileName = "numbers.txt";
    generateSeats();

    connect(acceptButton, SIGNAL(clicked()), this, SLOT(onAcceptButtonClicked()));

}

ReserveSeatsWindow::~ReserveSeatsWindow()
{
    delete layout;
}

void ReserveSeatsWindow::generateSeats()
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Could not open file");
        return;
    }

    QTextStream in(&file);
    int row = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();

        for (int col = 0; col < line.size(); ++col) {

            QChar number = line[col]; // type of seat (0 - free, 1 - special, 2 - vip )
            Seat* seat = new Seat(row, col, number); // create seat object

            connect(seat, &Seat::clicked, this, &ReserveSeatsWindow::onButtonClicked);
            layout->addWidget(seat->getButton(), row + 1, col + 1); // add button to layout
        }

        // add label with row letter
        QLabel* rowLabel = new QLabel(QString(QChar('A' + row)));
        layout->addWidget(rowLabel, row + 1, 0);

        ++row;
    }

    file.close();
}

void ReserveSeatsWindow::onButtonClicked(int row, int col)
{
    QString seatNumber = QString(QChar('A' + row)) + QString::number(col + 1);

    //check if seat is reserved
    if (std::find(reservedSeats.begin(), reservedSeats.end(), seatNumber) != reservedSeats.end()) {
        //remove seat from reservedSeats
        reservedSeats.erase(std::remove(reservedSeats.begin(), reservedSeats.end(), seatNumber), reservedSeats.end());

       //QMessageBox::information(nullptr, "Seat Clicked", QString("Seat %1 unclicked").arg(seatNumber));
    }
    else {
        //add seat to reservedSeats
        reservedSeats.push_back(seatNumber);

        //QMessageBox::information(nullptr, "Seat Clicked", QString("Seat %1 clicked").arg(seatNumber));

    }
}

std::vector<QString> ReserveSeatsWindow::getReservedSeats() const
{
    return reservedSeats;
}

bool ReserveSeatsWindow::isSeatReserved()
{
    if (reservedSeats.size() > 0) return true;
    return false;
}


void ReserveSeatsWindow::onAcceptButtonClicked()
{
    if (reservedSeats.size() == 0) {
		QMessageBox::information(nullptr, "Error", "You need to reserve at least one seat.");
	}
    else {
		QMessageBox::information(nullptr, "Success", "Seats reserved successfully.");
	}
}
