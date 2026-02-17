//
// Created by jammy on 19/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_AIRPLANE_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_AIRPLANE_H

#include <iostream>
#include <fstream>
using namespace std;

#include "Engine/Engine.h"
#include "Empennage/Empennage.h"
#include "Wing/Wing.h"
#include "Landing_Gear/LandingGear.h"
#include "Fuselage/Fuselage.h"
#include "Fuselage/PassengerFuselage.h"
#include "Fuselage/CargoFuselage.h"

#include "../nlohmann/json.hpp"

using json = nlohmann ::json;

class Airplane {
  string planeID;
  static int increment;
  string planeType;
  bool isAvailable;   // Check whether plane is available for flight, or under maintenance
  bool isFlight;   // Check if plane is in flight

  json planeMaintenanceRecord;   // record for maintenance of a plane

  json bookedSeats;   // variable for booked seats

  /* Components below are for maintenance and repairing purposes only */
  vector<Engine> engines;
  Wing wings[2];
  Empennage empennage;
  LandingGear mainLandingGear[2];
  LandingGear noseLandingGear;
  Fuselage * fuselage;

public:

  Airplane( const string & planeType, int engines,
           int aisles, int rows, int cols );   // Passenger Plane

  Airplane(int capacity, json & items );   // Cargo Plane

  void displayAirplaneStatus();

  json & getPlaneMaintenanceRecord();   // getter for maintenance record
  void readMaintenanceRecord();   // read maintenance record
  void editMaintenanceRecord();   // rewrite / modify maintenance record

  json & getBookedSeats();   // get bookedSeats IDs
  void readBookedSeats();   // read bookedSeats record
  void writeBookedSeats();   // write bookedSeats record

  string getPlaneID();
  string getPlaneType();

  void setPlaneAvailability( bool value );
  bool isPlaneAvailable();

  void setFlightStatus( bool value );
  bool getFlightStatus();

  void writeFlightStatus( bool value );
  json readFlightStatus();

  vector <Engine> & getEngines();
  Empennage & getEmpennage();
  LandingGear * getMainLandingGear();
  LandingGear & getNoseLandingGear();

  vector <Window> &getWindows( int column );
  vector <vector <PlaneSeat*> > &getPlaneSeats();

  Fuselage * getFuselage();

  Wing * getWings();

  Airplane & getAirPlane();

  void displaySeats();  // Samer Function

  void setSeatPrice(double &hours);   // Samer Function

  double getSeatPrice(string & ID);   // Samer Function

  void setSeat(const string &ID, bool value);   // Samer Function

};


#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_AIRPLANE_H
