#include "Ticket.h"
#include "Schedule.h"

Ticket::Ticket(char row, int seat, double price, Schedule& schedule)
    : row(row), seat(seat), price(price), schedule(schedule)
{
}

char Ticket::getRow() const
{
    return row;
}

double Ticket::getPrice() const
{
    return price;
}

int Ticket::getSeat() const
{
    return seat;
}
Schedule& Ticket::getSchedule() 
{
    return schedule;
}
