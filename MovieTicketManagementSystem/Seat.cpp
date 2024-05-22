#include "Seat.h"
#include <QPushButton>
#include <QString>

Seat::Seat(int row, int col, QChar type) : seatRow(row), seatCol(col), seatType(type)
{
    seatNumber = QString(QChar('A' + seatRow)) + QString::number(seatCol + 1);
    button = new QPushButton(seatNumber);
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

bool Seat::chooseSeat()
{
    isSelected = !isSelected;
    updateColor();

    return isSelected;
}

void Seat::setSeat(bool variable)
{
    isSelected = variable;

    updateColor();

}

QChar Seat::type() const
{
    return seatType;
}


QString Seat::getSeatNumber() const
{
    return seatNumber;
}

bool Seat::isSelectedSeat() const
{
    return isSelected;
}

void Seat::resetSeat()
{
    setEnabled(true);
    setSeat(false);
    button->setChecked(false);
}

void Seat::setEnabled(bool variable)
{
    this->button->setEnabled(variable);
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
    emit clicked(getSeatNumber());
}