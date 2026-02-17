//
// Created by Scorp Radoz on 23/04/2024.
//

#ifndef CUSTOMERS_JSON_BOOKEDTICKETS_H
#define CUSTOMERS_JSON_BOOKEDTICKETS_H

#include "ctime"
#include "Ticket.h"

class BookedTickets : public Ticket {
    double price;
    time_t bookingTime;
    bool isPaid;


public:
    BookedTickets( const std::string ID,const std::string &departure, const std::string &destination, const std::string &flightnumber,
                  std::string seatNumber);//No definiton yet
    friend std::istream &operator>>(std::istream &is, BookedTickets &bookedTicket);

    time_t getBookingTime() {
        return bookingTime;
    }

    bool getIsPaid() {
        return isPaid;
    }

    double getPrice() {
        return price;
    }

    void setPrice(double p) { price = p; }

    void setBookingTime(time_t bt) { bookingTime = bt; }

    void setIsPaid(bool value) {
        isPaid = value;
    }

    friend std::ostream &operator<<(std::ostream &os, const BookedTickets &ticket);

    bool operator==(const BookedTickets &other) const;

};

inline std::istream &operator>>(std::istream &is, BookedTickets &bookedTicket) {
    std::cout << "Enter Passenger Name: ";
    getline(is, bookedTicket.passengerName);

    std::cout << "Enter Passenger Age: ";
    getline(is, bookedTicket.passengerAge);

    std::cout << "Enter CNIC: ";
    getline(is, bookedTicket.CNIC);

    time_t now = time(NULL);
    bookedTicket.bookingTime = now; //Store the current time as the booking time of this ticket
    return is;
}


#endif //CUSTOMERS_JSON_BOOKEDTICKETS_H
