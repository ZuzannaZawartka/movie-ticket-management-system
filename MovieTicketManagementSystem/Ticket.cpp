#include "Ticket.h"
#include "Movie.h"

Ticket::Ticket(char row, int seat, double price, Movie& movie)
    : row(row), seat(seat), price(price), movie(movie)
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
Movie& Ticket::getMovie() const
{
    return movie;
}
