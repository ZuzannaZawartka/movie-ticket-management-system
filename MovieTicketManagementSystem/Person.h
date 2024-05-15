#pragma once
#include <QString>
#include <vector>
#include "Ticket.h"

class Person
{
public:
	Person(const QString& name, const QString& email, std::vector<Ticket>& tickets, const QString& phoneNumber);
	QString getPhoneNumber() const;
	QString getName() const;
	QString getEmail() const;
	std::vector<Ticket> getTicketArray() const;
private:
	QString name;
	QString email;
	std::vector<Ticket> tickets;
	QString phoneNumber;
};