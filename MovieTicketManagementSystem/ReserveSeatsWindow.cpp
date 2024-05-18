#include "ReserveSeatsWindow.h"
#include <QFile>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include "Seat.h"


ReserveSeatsWindow::ReserveSeatsWindow(QGridLayout* layout) :layout(layout)
{
	fileName = "numbers.txt";
	generateSeats();
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

            QChar number = line[col]; // Aktualna liczba okreœla typ miejsca (0 - zajête, 1 - normalne, 2 - VIP)
            Seat* seat = new Seat(row, col, number); // Tworzymy nowe miejsce na podstawie odczytanej liczby

            connect(seat, &Seat::clicked, this, &ReserveSeatsWindow::onButtonClicked);
            layout->addWidget(seat->getButton(), row + 1, col + 1); // Dodajemy etykietê miejsca do layoutu
        }

        // Dodajemy etykietê z numerem rzêdu
        QLabel* rowLabel = new QLabel(QString(QChar('A' + row)));
        layout->addWidget(rowLabel, row + 1, 0);

        ++row;
    }

    file.close();
}

void ReserveSeatsWindow::onButtonClicked(int row, int col)
{
	QMessageBox::information(nullptr, "Info", "Seat clicked: " + QString(QChar('A' + row)) + QString::number(col + 1));
}