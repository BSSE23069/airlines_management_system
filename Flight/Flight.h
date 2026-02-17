//
// Created by Scorp Radoz on 21/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_FLIGHT_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_FLIGHT_H

#include "iostream"
#include "../Airplane/Airplane.h"
#include "Crew/Crew.h"
#include "Ticket.h"
#include "BookedTickets.h"
#include "../nlohmann/json.hpp"
#include "../Accounts/Account.h"
using namespace std;
using json = nlohmann::json;

class Flight {
    std::string departure;
    time_t departureTime;
    time_t arrivalTime;
    std::string destination;
    int availableSeats;
    std::string flightNumber;
    std::string planeID;
    std::vector<Ticket> tickets;
    std::vector<BookedTickets> bookedTickets;
    json jsonTickets = json::array();
    json jsonBookedTickets =json::array();

    // Assuming Crew, Passenger, Airplane, and AirportFacilities are defined elsewhere
    Crew *crew;
    Airplane *aircraft;
    //AirportFacilities* facilities;

public:
    Flight(const std::string &departure, const std::string &destination,
           const std::string &flightNumber/*, AirportFacilities* facilities*/);

    Ticket buySeat( std::string customerID);

    void readFlight(json j);

    BookedTickets bookSeat(std::string customerID);

    void checkBookingTime();

    void setCrew(Crew value);

    bool checkTicket();

    void createTicket() {
        // Implementation depends on the Ticket class
    }

    bool setArrivalAndDeparture(std::string &s);

    void setArrival();

    void displayBookedAndNormalSeats();

    std::string getDeparture();

    std::string getDestination();

    std::string getFlightNumber();

    int getAvailableSeats();

    void setAvailableSeats(int seats){
        availableSeats=seats;
    }

    void setAirplane(Airplane &airplane);

    bool checkBookedTicket(BookedTickets &ticket);

    void writeBookedTicketsToJson(BookedTickets &ticket);

    void writeTicketsToJson(Ticket &ticket);

    void displayFlight();

    void setSeatPrice(double hours);

    void removeAlltheTickets(std::string flightID);

    void removeBookedTicket(BookedTickets &ticket);

    Airplane* getAirCraft();

    Crew* getCrew ();

    time_t getDepartureTime(){
        return departureTime;
    }

    time_t getArrivalTime(){
        return arrivalTime;
    }

    string getPlaneID(){
        return planeID;
    }

    void setDeparture(std::string dep) {
        departure = dep;
    }

    void setDepartureTime(time_t depTime) {
        departureTime = depTime;
    }

    void setArrivalTime(time_t arrTime) {
        arrivalTime = arrTime;
    }

    void setDestination(std::string dest) {
        destination = dest;
    }

    void setAvailableSeats() {
        availableSeats = aircraft->getPlaneSeats().size();
    }

    void setFlightNumber(std::string flightNum) {
        flightNumber = flightNum;
    }

    void setPlaneID(std::string id) {
        planeID = id;
    }

    bool isCNICav(std::string CNIC);

    bool inputDetails(Ticket & ticket);
};


#endif //INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_FLIGHT_H
