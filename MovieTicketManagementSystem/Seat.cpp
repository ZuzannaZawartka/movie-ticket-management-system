#include "Seat.h"
#include <QPushButton>
#include <QString>

Seat::Seat(int row, int col, QChar type,QWidget* parent) : QObject(parent), seatRow(row), seatCol(col), seatType(type)
{
    seatNumber = QString(QChar('A' + seatRow)) + QString::number(seatCol + 1);
    button = new QPushButton(seatNumber, parent);
    button->setCheckable(true);
    button->setStyleSheet("background-color: lightgray;");
    updateColor();

    connect(button, &QPushButton::clicked, this, &Seat::onButtonClicked);
}

Seat::~Seat()
{
    delete button;
}


QPushButton* Seat::getButton() const
{
    return button;
}

int Seat::row() const
{
    return seatRow;
}

int Seat::col() const
{
    return seatCol;
}

QChar Seat::type() const
{
    return seatType;
}

bool Seat::takeSeat()
{
    isSelected = !isSelected;

    updateColor();

    return isSelected;
}

QString Seat::getSeatNumber() const
{
    return seatNumber;
}

void Seat::updateColor()
{
    if (isSelected)
    {
        button->setStyleSheet("background-color: grey;");
        return;
    }

    switch (seatType.unicode()) {
    case '0':
        button->setStyleSheet("background-color: red;");
        break;
    case '1':
        button->setStyleSheet("background-color: green;");
        break;
    case '2':
        button->setStyleSheet("background-color: gold;");
        break;
    default:
        button->setStyleSheet("");
        break;
    }
}

void Seat::onButtonClicked()
{
    takeSeat();
    emit clicked(seatRow, seatCol);
}