//
// Created by jammy on 19/04/2024.
//

#include <sstream>
#include "Company.h"

Company * ::Company ::company = 0;

Company ::Company() : name("AirTaxi") { }

Company *Company ::getCompany() {
  if(!company)
    company = new Company;
  return company;
}

void Company ::purchaseAirPlane(vector<Airplane> & planes) {

  string number;
  string choice;

  while(true)
  {
    cout << "[1] AirTaxi_120" << endl;   // Short-Haul Plane --- 120 seats, 1 aisle, 3 seats on each side of aisle
    cout << "[2] AirTaxi_210" << endl;   // Medium-Haul Plane --- 210 seats, 2 aisles, 2-3-2 seats orientation
    cout << "[3] AirTaxi_400" << endl;   // Long-Haul Plane ---  400 seats, 2 aisles, 3-4-3 seats orientation
    cout << "[4] AirTaxi_Cargo" << endl;
    cout << "[5] Exit Viewing" << endl;
    cout << "Enter corresponding number to view details, or exit menu" << endl;

    getline(cin, number);

    if( choiceChecker(number, 1, 5) != "ERROR")
    {
      if( number == "1" )
      {
        cout << "            20 rows, 120 seats, 1 aisle, 3 seats on each side" << endl;
        cout << "2 Engines, 2 main landing gears of 4 tyres, and a nose landing gear of 2 tyres" << endl << endl;
        cout << "                     ***  PRICE : 1 CRORE PKR/-  ***                          " << endl;

        cout << "Would you like to purchase the aircraft ? Yes(1) OR No(0)" << endl;
        cin >> choice;
        cout << endl;

        if( choiceChecker(choice, 0, 1) != "ERROR" )
        {
          if( choice == "1" )
          {
            if(companyAccount.addBalanceUnknownAcc("company123",1000000,"Plane maintainance"))
            {
              // Adding plane to Airlines collection
              planes.emplace_back("AirTaxi_120",2,1,20,6);
              cout << "AirTaxi_120 Aircraft successfully purchased !" << endl;
              writePlanesFile(planes);

              return;
            }
          }
        }
        else
          cout << "!! Invalid Input !!" << endl;

      }
      else if( number == "2" )
      {
        cout << "            30 rows, 210 seats, 2 aisles, 2-3-2 seats orientation" << endl;
        cout << "2 Engines, 2 main landing gears of 8 tyres, and a nose landing gear of 2 tyres" << endl << endl;
        cout << "                     ***  PRICE : 2 CRORE PKR/-  ***                          " << endl;

        cout << "Would you like to purchase the aircraft ? Yes(1) OR No(0)" << endl;
        cin >> choice;
        cout << endl;

        if( choiceChecker(choice, 0, 1) != "ERROR" )
        {
          if( choice == "1" )
          {
            if(companyAccount.addBalanceUnknownAcc("company123",2000000,"Plane maintainance"))
            {
              // Adding plane to Airlines collection
              planes.emplace_back("AirTaxi_210",4,2,30,7);
              cout << "AirTaxi_210 Aircraft successfully purchased !" << endl;
              writePlanesFile(planes);

              return;
            }
          }
        }
        else
          cout << "!! Invalid Input !!" << endl;
      }
      else if( number == "3" )
      {
        cout << "           40 rows, 400 seats, 3 aisles, 3-4-3 seats orientation" << endl;
        cout << "2 Engines, 2 main landing gears of 12 tyres, and a nose landing gear of 2 tyres" << endl << endl;
        cout << "                     ***  PRICE : 3 CRORE PKR/-  ***                          " << endl;

        cout << "Would you like to purchase the aircraft ? Yes(1) OR No(0)" << endl;
        cin >> choice;
        cout << endl;

        if( choiceChecker(choice, 0, 1) != "ERROR" )
        {
          if( choice == "1" )
          {
            if(companyAccount.addBalanceUnknownAcc("company123",3000000,"Plane maintainance"))
            {
              // Adding plane to Airlines collection
              planes.emplace_back("AirTaxi_400",4,2,40,10);
              cout << "AirTaxi_400 Aircraft successfully purchased !" << endl;
              writePlanesFile(planes);

              return;
            }
          }
        }
        else
          cout << "!! Invalid Input !!" << endl;
      }
      else if( number == "4" )
      {
        cout << "   Cargo Plane, with a compartment having a capacity of 1000 box-shaped items" << endl;
        cout << "4 Engines, 2 main landing gears of 8 tyres, and a nose landing gear of 2 tyres" << endl << endl;
        cout << "                     ***  PRICE : 1.5 CRORE PKR/-  ***                          " << endl;

        cout << "Would you like to purchase the aircraft ? Yes(1) OR No(0)" << endl;
        cin >> choice;
        cout << endl;

        if( choiceChecker(choice, 0, 1) != "ERROR" )
        {
          if( choice == "1" )
          {
            if(companyAccount.addBalanceUnknownAcc("company123",1500000,"Plane maintainance"))
            {
              json items;   // empty items
              // Adding plane to Airlines collection
              planes.emplace_back(1000, items);
              cout << "AirTaxi_Cargo Aircraft successfully purchased !" << endl;
              writePlanesFile(planes);

              return;
            }
          }
        }
        else
          cout << "!! Invalid Input !!" << endl;

      }
      else if( number == "5" )
        break;
    }
    else
      cout << "!! Invalid Input !!" << endl;



    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

}

void Company ::readPlanesFile( vector<Airplane> & planes ) {

  if(planes.empty())
  {
    json existingPlanes;

//      ifstream inFile("C:\\Users\\Scorp Radoz\\Documents\\GitHub\\2024-Spring-SE102TB-Project-se102b-e\\Company\\AirplanesFile.json"); //ssamerss
       ifstream inFile(R"(C:\OOPS_PROJECT_EXTENDED\2024-Spring-SE102TB-Project-se102b-e\Company\AirplanesFile.json)");//jamzee
//    ifstream inFile ("Company\\AirplanesFile.json");
    if(!inFile.is_open())
    {
      cout << "--- NO EXISTING AIRPLANES ---" << endl;
      return;
    }

    inFile >> existingPlanes;
    inFile.close();

    for (int i = 0; i < existingPlanes.size(); ++i) {
      if( existingPlanes[i] == "AirTaxi_120" )
        planes.emplace_back(existingPlanes[i],2,1,20,6);
      else if( existingPlanes[i] == "AirTaxi_210" )
        planes.emplace_back(existingPlanes[i],4,2,30,7);
      else if( existingPlanes[i] == "AirTaxi_400" )
        planes.emplace_back(existingPlanes[i],4,2,40,10);
      else if( existingPlanes[i] == "AirTaxi_Cargo" ) {
        json items;   // empty items
        planes.emplace_back(1000, items); }
    }

    for (int i = 0; i < planes.size(); ++i)
    {
      if( !planes[i].getPlaneMaintenanceRecord().empty() )
      {
        json availabilityCheck;
        availabilityCheck = planes[i].getPlaneMaintenanceRecord()[planes[i].getPlaneMaintenanceRecord().size() - 1];
        if( availabilityCheck["isAvailable"] == false )
          planes[i].setPlaneAvailability(false);
      }
    }


    for (int i = 0; i < planes.size(); ++i) {
      planes[i].readFlightStatus();
    }


  }
  else
    cout << "!! Airplanes Exist Already !!" << endl;


}

void Company ::writePlanesFile( vector<Airplane> &planes ) {

  json existingPlanes = json ::array();
  for (int i = 0; i < planes.size(); ++i) {
    existingPlanes.push_back(planes[i].getPlaneType());
  }
  /*  --> SAMER <--  */
//  ofstream outFile("C:\\Users\\Scorp Radoz\\Documents\\GitHub\\2024-Spring-SE102TB-Project-se102b-e\\Company\\AirplanesFile.json", ios::trunc);
  /*  --> JAMZEE <--  */
   ofstream outFile(R"(C:\OOPS_PROJECT_EXTENDED\2024-Spring-SE102TB-Project-se102b-e\Company\AirplanesFile.json)", ios::trunc);
//  ofstream outFile ("Company\\AirplanesFile.json");
  outFile << existingPlanes;
  outFile.close();
}