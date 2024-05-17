#include <iostream>
#include "Person.h"
#include "Ticket.h"
#include "Movie.h"
using namespace std;
int main() {
    Ticket ticket('A', 5, 25.0, Movie("Title", "Director", "Type", 120));
    //Person person("John Doe", "john@example.com", ticket, "+123456789");

    /* Wyœwietlanie informacji o person
    cout << "name: " << person.getName() << endl;
    cout << "email: " << person.getEmail() << endl;
    cout << "ticket:" << endl;
    const std::vector<Ticket>& tickets = person.getTicketArray();
    for (const auto& t : tickets) {
        cout << "  Seat: " << t.getSeat() << ", Row: " << t.getRow() << ", Price: " << t.getPrice() << endl;
    }
    cout << "number:" << person.getPhoneNumber() << endl;

    */
    cout << ticket.getRow() << endl;
    return 0;
}