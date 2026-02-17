//
// Created by Scorp Radoz on 23/04/2024.
//

#include "BookedTickets.h"

BookedTickets::BookedTickets( const std::string ID,const std::string &departure1, const std::string &destination1,
                             const std::string &flightNumber1, std::string seatNumber1):Ticket(ID,departure1,destination1,flightNumber1,seatNumber1) {
}

std::ostream &operator<<(std::ostream &os, const BookedTickets &ticket) {
    os << "Passenger Name: " << ticket.passengerName << "\n"
       << "Passenger Age: " << ticket.passengerAge << "\n"
       << "CNIC: " << ticket.CNIC << "\n"
       << "Departure: " << ticket.departure << "\n"
       << "Departure time: " << ctime(&ticket.departureTime) << "\n"
       << "Destination: " << ticket.destination << "\n"
       << "Arrival time: " << ctime(&ticket.destinationTime) << "\n"
       << "Flight Number: " << ticket.flightNumber << "\n"
       << "Seat Number: " << ticket.seatNumber << "\n"
       << "Seat Price: " << ticket.price << "\n"
       << "================================================\n";
    return os;
}

bool BookedTickets::operator==(const BookedTickets& other) const {
    return passengerName == other.passengerName
           && passengerAge == other.passengerAge
           && CNIC == other.CNIC
           && departure == other.departure
           && destination == other.destination
           && flightNumber == other.flightNumber
           && seatNumber == other.seatNumber
           && departureTime == other.departureTime
           && destinationTime == other.destinationTime;
}


