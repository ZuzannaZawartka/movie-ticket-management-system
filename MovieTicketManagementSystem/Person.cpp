#include "Person.h"


Person::Person(const QString& name, const QString& email, std::vector<Ticket>& tickets, const QString& phoneNumber)
    : name(name), email(email), tickets(tickets), phoneNumber(phoneNumber)
{
}

QString Person::getName() const
{
    return name;
}

QString Person::getEmail() const
{
    return email;
}

std::vector<Ticket> Person::getTicketArray() const
{
    return tickets;
}

QString Person::getPhoneNumber() const
{
    return phoneNumber;
}