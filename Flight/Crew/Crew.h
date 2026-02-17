//
// Created by Scorp Radoz on 21/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_CREW_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_CREW_H
#include "iostream"
#include "vector"
class Crew {
private:
    int crewNumber;
    // static int ID;
    std::string pilotID;
    std::string coPilotID;
    std::string purserID;
    std::string flightNumber;
    // std::string pilot;
    // std::string copilot;
    // std::string purser;

    std::vector<std::string> flightAttendant;
    std::vector<std::string> medic;

public:
    Crew(){
         
        crewNumber = 0;
    }

    
    // void replaceCrew();
    std::string getFlightNumber(){
        return flightNumber;
    }
    void setPilot(const std::string &pilot);

    void setCoPilot(const std::string &copilot);

    void setPurser(const std::string &purser);

    void setFlightAttendant(const std::string &flightAttendant);

    void setMedic(const std::string &medic);

    std::vector<std::string> getMedic();

    std::string getPurser();

    std::string getPilot();

    std::string getCoPilot();
//          ..\\Employee\\

    void setFlightNumber(std::string );

    int getCrewNumber();
    
    friend std::ostream& operator<<(std::ostream& os, const Crew& crew);

    void setCrewNumber(int value);

    std::vector<std::string> getFlightAttendant();

    friend std::ostream &operator<<(std::ostream &os, const Crew &crew);

};

#endif //INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_CREW_H
