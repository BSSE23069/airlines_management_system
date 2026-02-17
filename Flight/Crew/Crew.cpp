//
// Created by Scorp Radoz on 21/04/2024.
//

#include "Crew.h"

std::vector<std::string> Crew::getFlightAttendant() {
    return flightAttendant;
}

std::vector<std::string> Crew::getMedic() {
    return medic;
}

std::string Crew::getPurser() {
    return purserID;
}
std::string Crew::getPilot() {
    return pilotID;
}

std::string Crew::getCoPilot() {
    return coPilotID;
}
void Crew::setFlightAttendant(const std::string &flightAttendant) {
    this->flightAttendant.push_back(flightAttendant);
}

void Crew::setMedic(const std::string &medic) {
    this->medic.push_back(medic);
}
// void Crew::setFlightNumber(std::string number){
//     flightNumber=number;
// }


void Crew::setPurser(const std::string &purser) {
    this->purserID = purser;
}

void Crew::setPilot(const std::string &pilot) {
    this->pilotID = pilot;
}

void Crew::setCoPilot(const std::string &copilot) {
    this->coPilotID = copilot;
}

std::ostream& operator<<(std::ostream& os, const Crew& crew) {
    os << "Crew Number : "<<crew.crewNumber<<"\n";
    os << "Pilot: " << crew.pilotID << "\n";
    os << "Co-Pilot: " << crew.coPilotID << "\n";
    os << "Purser: " << crew.purserID << "\n";

    os << "Flight Attendants: ";
    for (const auto& attendant : crew.flightAttendant) {
        os << attendant << ", ";
    }
    os << "\n";

    os << "Medics: ";
    for (const auto& medic : crew.medic) {
        os << medic << ", ";
    }
    os << "\n";

    return os;
}

void Crew :: setCrewNumber(int value){
    crewNumber = value;
}

void Crew :: setFlightNumber(std::string value){
    flightNumber = value;
 
}

int Crew :: getCrewNumber(){
        return crewNumber;
}



