//
// Created by jammy on 24/04/2024.
//

#ifndef AIRPLANEMAINTENANCE_H
#define AIRPLANEMAINTENANCE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>
#include <chrono>
#include "../nlohmann/json.hpp"
#include "../ErrorHandler/ErrorHandler.h"
#include <chrono>

using namespace std;

using json = nlohmann :: json;

#include "../Airplane/Airplane.h"
#include "../Departments/Department.h"
#include "../Employees/Employee.h"
#include "../Employees/InspectionManager.h"
#include "../Employees/Technician.h"

class AirplaneMaintenance : public Department
{
  json planeCosts;
  json repairDurations;

  json temporaryRecord;   // temporary maintenance record for a plane

  vector <Airplane> * planes;
  vector <Employee *> * employees;

  Account AirplaneMaintenanceAccount;

public:
AirplaneMaintenance();
  AirplaneMaintenance( vector<Airplane> & planes, vector<Employee*>  & employees );

  // inspection functions
  void inspectAirplane( const string & planeID );

  void inspectEngines( const string & planeID );
  void inspectEmpennage( const string & planeID );

  void inspectMainLandingGears( const string & planeID );
  void inspectNoseLandingGear( const string & planeID );

  void inspectWindows( const string & planeID );
  void inspectSeats( const string & planeID );
  void inspectWings( const string & planeID );

  void writeLandedPlanes( const string & planeID, const string & action );
  json readLandedPlanes();

  // Display Landed Planes for Inspection
  void displayLandedPlanes();

  // Check if a given plane ID exists in LandedPlanes File
  bool checkLandedPlanesFile( const string &planeID );

  // Display Unavailable / Faulty planes
  void displayUnavailablePlanes();

  // Display Available planes
  void displayAvailablePlanes();

  // total cost for maintenance of a plane
  void generateBills( const string & planeID );

  // side functions
  int getPlaneIndex( const string & planeID );   // returns plane index based on ID
  void getFaultyParts( int partsTotal, int parts[], int min_val, int max_val );

  // file readers
  void readPlaneCosts();
  void displayPlaneCosts();

  // employees functions
  bool checkForEmployees();
  json assignEmployees();

  // display seats details
  void displaySeatsInfo();

  void maintenanceMenu();

};

#endif // AIRPLANEMAINTENANCE_H
