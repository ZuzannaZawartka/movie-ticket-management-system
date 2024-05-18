#include "Seat.h"
#include <QLabel>
#include <QString>

Seat::Seat(int row, int col, QChar type,QWidget* parent) : QObject(parent), seatRow(row), seatCol(col), seatType(type)
{
    seatNumber = QString(QChar('A' + seatRow)) + QString::number(seatCol + 1);
    label = new QLabel(seatNumber);
    label->setAlignment(Qt::AlignCenter);
    label->setFrameStyle(QFrame::Box | QFrame::Plain);
    updateColor();

    connect(label, &QLabel::linkActivated, this, &Seat::onLinkActivated);
}

Seat::~Seat()
{
    delete label;
}


QLabel* Seat::getLabel() const
{
    return label;
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
        label->setStyleSheet("background-color: grey;");
        return;
    }

    switch (seatType.unicode()) {
    case '0':
        label->setStyleSheet("background-color: red;");
        break;
    case '1':
        label->setStyleSheet("background-color: green;");
        break;
    case '2':
        label->setStyleSheet("background-color: gold;");
        break;
    default:
        label->setStyleSheet("");
        break;
    }
}

void Seat::onLinkActivated()
{
    takeSeat();

    emit clicked(seatRow, seatCol);

}