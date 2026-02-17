//
// Created by Scorp Radoz on 21/04/2024.
//

#include "Ticket.h"

Ticket::Ticket(  const std::string ID,const std::string& departure, const std::string& destination, const std::string& flightnumber, std::string seatNumber) : customerID(ID),departure(departure), destination(destination), flightNumber(flightnumber),
                                 seatNumber(seatNumber) {}

std::istream &operator>>(std::istream &is, Ticket &ticket) {




    std::cout << "Enter CNIC: ";
    is.ignore();
    getline(is, ticket.CNIC);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
    os << "Passenger Name: " << ticket.passengerName << "\n"
       << "Passenger Age: " << ticket.passengerAge << "\n"
       << "CNIC: " << ticket.CNIC << "\n"
       << "Departure: " << ticket.departure << "\n"
       << "Departure time: "<<ctime(&ticket.departureTime)<<"\n"
       << "Destination: " << ticket.destination << "\n"
       << "Arrival time: "<<ctime(&ticket.destinationTime)<<"\n"
       << "Flight Number: " << ticket.flightNumber << "\n"
       << "Seat Number: " << ticket.seatNumber << "\n"
       << "================================================\n";
       return os;
}

bool Ticket::readingTicket(time_t DepartureTime,time_t Arrival, std::string Departure, std::string arrival, std::string flightID) {
    if(DepartureTime==departureTime&&Arrival==destinationTime&&destination==arrival&&flightNumber==flightID&&Departure==departure){
        return true;
    }
    return false;
}
