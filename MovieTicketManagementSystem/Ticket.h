#pragma once
#include <QString>
#include <Movie.h>

class Ticket
{
public:
	Ticket(char row, int seat, double price, Movie& movie);
	int getSeat() const;
	char getRow() const;
	double getPrice() const;
	Movie& getMovie() const;

private:
	char row;
	int seat;
	Movie& movie;
	double price;

};

