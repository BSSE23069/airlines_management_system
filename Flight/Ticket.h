//
// Created by Scorp Radoz on 21/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_TICKET_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_TICKET_H

#include "iostream"

class Ticket {
protected:
    std::string customerID;
    std::string passengerName;
    std::string passengerAge;
    std::string CNIC;
    std::string departure;
    std::string destination;
    std::string flightNumber;
    std::string seatNumber;
    time_t departureTime;
    time_t destinationTime;

public:
    Ticket(const std::string ID, const std::string &departure, const std::string &destination,
           const std::string &flightnumber, std::string seatNumber);

    Ticket() {}


    // friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket);
    friend std::istream &operator>>(std::istream &is, Ticket &ticket);

    friend std::ostream &operator<<(std::ostream &os, const Ticket &ticket);

    std::string getSeatNumber() {
        return seatNumber;
    }

    void setPassengerName(std::string name) {
        passengerName=name;
    }

    void setPassengerAge(std::string age) {
        passengerAge=age;

    }

    void addPassengerName() {
        std::cout << "Enter Passenger Name: ";
        std::cin.ignore();
        std::getline(std::cin, passengerName);
    }

    void addPassengerAge() {
        std::cout << "Enter Passenger Age: ";
        std::cin.ignore();
        std::getline(std::cin, passengerAge);
    }

    void setCNIC(std::string cnic) { CNIC = cnic; }

    void setDeparture(std::string dep) { departure = dep; }

    void setDestination(std::string dest) { destination = dest; }

    void setFlightNumber(std::string flightNum) { flightNumber = flightNum; }

    void setSeatNumber(std::string value) {
        seatNumber = value;
    }

    void setDepartureTime(time_t departureTime) {
        this->departureTime = departureTime;
    }

    void setDestinationTime(time_t destinationTime) {
        this->destinationTime = destinationTime;
    }

    void setCustomerId(std::string ID) {
        customerID = ID;
    }


    void setWholeTicket(Ticket &ticket);

    // Non-parameterized getters
    std::string getCustomerId() {
        return customerID;
    }

    std::string getPassengerName() { return passengerName; }

    std::string getPassengerAge() { return passengerAge; }

    std::string getCNIC() { return CNIC; }

    std::string getDeparture() { return departure; }

    std::string getDestination() { return destination; }

    std::string getFlightNumber() { return flightNumber; }

    time_t getDepartureTime() { return departureTime; }

    time_t getDestinationTime() { return destinationTime; }

    bool readingTicket(time_t DepartureTime, time_t Arrival, std::string Departure, std::string arrival,
                       std::string flightID);

    friend std::istream &operator>>(std::istream &is, Ticket &ticket);
};


#endif //INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_TICKET_H
