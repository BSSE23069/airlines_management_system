#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "../Users/User.h"
#include "../Flight/Ticket.h"
#include "../Flight/BookedTickets.h"
#include "../nlohmann/json.hpp"
#include "fstream"
using namespace std;
using json = nlohmann::json;
#include <vector>
class Customer : public User 
{
    //std::string bankAccount;
    std::vector<Ticket> tickets;
    std::vector<BookedTickets> bookedTickets;
    json jsonTickets;
    json jsonBookedTickets;
public:
    Customer ();
    // Customer (const std::string&, const std::string&);

    Customer (const std::string&, const std::string&, const std::string&, const std::string&);

   // void getTickets();

    void addTicket(Ticket ticket);

    void addBookedTicket(BookedTickets ticket);

    BookedTickets payPriceOfTickets();

    void readBookedTicketsFromJson();

    void readTicketFromJson();

    void  writeTicketsToJson(Ticket &ticket);

    void writeBookedTicketsToJson(BookedTickets &ticket);

    void removeBookedTicket(BookedTickets & ticket);

    void addTicketAfterPayingPrice(BookedTickets & bookedTickets1);

    void displayTicketsHistory();

    virtual bool login (const std::string&, const std::string&) const override;

    virtual void displayInfo() const override;
    
    friend std::ostream& operator << (std::ostream& os, const Customer& cus);
};

#endif // Customer class 