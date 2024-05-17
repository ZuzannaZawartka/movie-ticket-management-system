#pragma once
#include <QString>
#include <Schedule.h>

class Ticket
{
public:
	Ticket(char row, int seat, double price, Schedule& schedule);
	int getSeat() const;
	char getRow() const;
	double getPrice() const;
	Schedule& getSchedule();

private:
	char row;
	int seat;
	Schedule& schedule;
	double price;

};

