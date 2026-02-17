#ifndef _FLIGHT_DEPARTMENT_H_
#define _FLIGHT_DEPARTMENT_H_

#include "Department.h"
#include "AirplaneMaintenance.h"
#include "../Flight/Flight.h"
#include "vector"
#include "../Airplane/Airplane.h"
#include "../Employees/pilot.h"
#include "../Employees/Medic.h"
#include "../Customers/Customer.h"
#include "../Employees/FlightAttendant.h"
#include "../nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;
class FlightDepartment : public Department{

    std::vector<Pilot *>pilots;
    std::vector<Medic *>medics;
    std::vector<FlightAttendant *> flightAttendants;
    std::vector<Flight> flights;
    std::vector<Crew> crews;

    std::vector<Airplane> & airplanes;
    std::vector<Customer*>& customers; // Aggregated

    std::vector <Pilot* > usedPilots;
    std::vector <Medic* > usedMedic;
    std::vector <FlightAttendant* > usedFlightAttendants;
    json jsonFlights = json::array();
public:
    FlightDepartment(std::vector <Airplane> &airplane, std::vector<Customer*>& customers);

    //  FlightDepartment()
    //     : airplanes(dummyAirplanes), customers(dummyCustomers) {}



    int checkFlightNumber();
    bool checkPlaneID(std::string & ID);
    void readFlights();
    void assignCrewToFlights();
    void displayFlights();
    void addPassengers(int customerIndex);
    bool checkIfFightNumberAvailable(std::string number);
    void addFlight();
    bool checkArrivalAndDeparture(std::string departure, std::string arrival);
    void displayFlights(std::string departure, std::string arrival);
    void payPriceOfBookedTicket(int i);
    void displayAvailablePlanes();
    void removeFlightObject(Flight & flight);
    void makeNewCrew(); //To add new crews to the vector of crew in Flight Department
    void editCrew();
    void displayCrews(json& crewsJson, int& totalNoOfCrews);
    // void displaySpecificCrew(int crewIndex);
    void setCrew(json& crewsJson, int& index);
    bool verifyCrewMember(string ID);
    void addPurser(json& crewsJson, int& crewIndex);
    void addPilot(json& crewsJson, int& crewIndex);
    void addCoPilot(json& crewsJson, int& crewIndex);
    void addFlightAttendants (json& crewsJson, int& crewIndex);
    void addMedics (json& crewsJson, int& crewIndex);
    bool verifyEditedID(string newID, string previousID);
    void removeCrewMember(string removeID);
    void removeFlight(AirplaneMaintenance& maintainance);
    void sendObjectToWriteFlights(Flight flights);
    void saveFlightToFile();
    void loadCrews(json& crewsJson, int& totalNoOfCrews);
    void crewsMenu();
    void loadCrewEmployees();
    void saveCrewEmployees();
    void viewVectors();
    void incrementAndDecrementOfAvailableSeats(int);
    void adminEnd(AirplaneMaintenance& maintainance);
    template <typename T>
    void displayCrewTemplate(string type, vector <T> employees);
    void displayEmployees();
    void receivePilots(vector<Pilot *> pilotsVector, vector<FlightAttendant *> flightVector, vector<Medic *> medicVector);
    void displayCrewsOnDemand();
};


#endif // Flight Department
