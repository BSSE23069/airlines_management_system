//
// Created by jammy on 24/04/2024.
//

#include "AirplaneMaintenance.h"
AirplaneMaintenance::AirplaneMaintenance() {


}
AirplaneMaintenance ::AirplaneMaintenance(vector<Airplane> & planes, vector<Employee *>&employees)
    : Department("AirplaneMaintenance")
{
  this->planes = &planes;
  this->employees = &employees;

  temporaryRecord["Engines"] = json ::array();

  temporaryRecord["Empennage"];

  temporaryRecord["MainLandingGear"]["RightLandingGear"]["Struts"] = json ::array();
  temporaryRecord["MainLandingGear"]["RightLandingGear"]["Tyres"] = json ::array();
  temporaryRecord["MainLandingGear"]["LeftLandingGear"]["Struts"] = json ::array();
  temporaryRecord["MainLandingGear"]["LeftLandingGear"]["Tyres"] = json ::array();

  temporaryRecord["NoseLandingGear"]["Struts"] = json ::array();
  temporaryRecord["NoseLandingGear"]["Tyres"] = json ::array();

  temporaryRecord["Seats"] = json ::array();

  temporaryRecord["Windows"] = json ::array();

  // planeCosts would be set according to file PlaneCosts
  // File has an array of 4 json objects
  // First 3 indices represent AirTaxi_120, AirTaxi_210, AirTaxi_240 costs respectively
  // Last index represent AirTaxi_Cargo costs

  readPlaneCosts();

}

void AirplaneMaintenance ::readPlaneCosts() {

  ifstream inFile(R"(C:\OOPS_PROJECT_EXTENDED\2024-Spring-SE102TB-Project-se102b-e\Departments\PlaneCosts.json)");  //Jamzee
//    ifstream inFile(" C:\\Users\\Scorp Radoz\\OneDrive\\Documents\\GitHub\\old\\2024-Spring-SE102TB-Project-se102b-e \\Departments\\PlaneCosts.json"); //SAMERS

//  ifstream inFile ("C:\\Users\\User\\OneDrive\\Desktop\\PROJECT\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\PlaneCosts.json");
  if( !inFile.is_open() )
  {
    cout << "!! ERROR OPENING PLANE COSTS FILE !!" << endl;

    return;
  }
  inFile >> planeCosts;
  inFile.close();

}

void AirplaneMaintenance ::displayPlaneCosts() {

  int x;

  while(true)
  {
    system("clear");
    cout << endl;
    cout << "[1] AirTaxi_120" << endl;
    cout << "[2] AirTaxi_210" << endl;
    cout << "[3] AirTaxi_400" << endl;
    cout << "[4] AirTaxi_Cargo" << endl;
    cout << "[5] Exit Viewing" << endl;

    do{
      cin >> x;
      cout << endl;
    } while( !( x >= 1 && x <= 5) );

    if( x == 5 )
      return;

    cout << " -- EMPENNAGE COSTS -- " << endl;
    cout << " -- Elevator : " << planeCosts[x-1]["Empennage"]["Elevator"] << " pkr -- " << endl;
    cout << " -- Rudders : " << planeCosts[x-1]["Empennage"]["Rudders"] << " pkr -- " << endl;
    cout << endl;

    cout << " -- ENGINE COSTS -- " << endl;
    cout << " -- Engine : " << planeCosts[x-1]["Engine"] << " pkr -- " << endl;
    cout << endl;

    cout << " -- LANDING GEAR COSTS -- " << endl;
    cout << " -- MAIN LANDING GEAR -- " << endl;
    cout << " -- TYRE : " << planeCosts[x-1]["LandingGear"]["MainLandingGear"]["Tyre"] << " pkr -- " << endl;
    cout << " -- STRUT : " << planeCosts[x-1]["LandingGear"]["MainLandingGear"]["Strut"] << " pkr -- " << endl;
    cout << " -- NOSE LANDING GEAR -- " << endl;
    cout << " -- TYRE : " << planeCosts[x-1]["LandingGear"]["NoseLandingGear"]["Tyre"] << " pkr -- " << endl;
    cout << " -- STRUT : " << planeCosts[x-1]["LandingGear"]["NoseLandingGear"]["Strut"] << " pkr -- " << endl;
    cout << endl;

    cout << " -- WINGS COSTS -- " << endl;
    cout << " -- Aileron : " << planeCosts[x-1]["Wings"]["Aileron"] << " pkr -- " << endl;
    cout << " -- Flaps : " << planeCosts[x-1]["Wings"]["Flaps"] << " pkr -- " << endl;
    cout << " -- Slats : " << planeCosts[x-1]["Wings"]["Slats"] << " pkr -- " << endl;
    cout << " -- Spoiler : " << planeCosts[x-1]["Wings"]["Spoiler"] << " pkr -- " << endl;
    cout << " -- Winglet : " << planeCosts[x-1]["Wings"]["Winglet"] << " pkr -- " << endl;
    cout << endl;

    if ( x != 4 )   // Check for Cargo Plane
    {
      cout << " -- PASSENGER COMPARTMENT -- " << endl;
      cout << " -- Seat : " << planeCosts[x-1]["PassengerCompartment"]["Seat"] << " pkr -- " << endl;
      cout << " -- Window : " << planeCosts[x-1]["PassengerCompartment"]["Window"] << " pkr -- " << endl;
    }
  }

}

int AirplaneMaintenance ::getPlaneIndex( const string & planeID ) {

  for (int i = 0; i < planes->size(); ++i) {
    if(planes->at(i).getPlaneID() == planeID )
      return i;
  }
  return -1;

}

void AirplaneMaintenance ::getFaultyParts(int partsTotal, int *parts, int min_val, int max_val) {

  // no. of ticks since epoch
  auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
  srand(seed);

  for (int i = 0; i < partsTotal; ++i) {
    parts[i] = min_val + rand() % (max_val - min_val + 1);
  }

}

void AirplaneMaintenance ::inspectEngines(const string &planeID)
{
  int x;
  cout << "[1] Defects found ?" << endl << "[0] Inspection positive ?" << endl;
  cin >> x;

  if(x)
  {
    planes->at(getPlaneIndex(planeID)).setPlaneAvailability(false); // detection of defects makes plane unavailable

    if( planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_120" )
    {
      int faultyParts[1];   // 1 of 2 engines
      getFaultyParts(1, faultyParts, 0, 1);   // random 1 engine is inspected to be damaged

      for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < planes->at(getPlaneIndex(planeID)).getEngines().size(); ++j) {
          if( faultyParts[i] == j )
          {
            planes->at(getPlaneIndex(planeID)).getEngines()[j].setEngineCondition(true);
            temporaryRecord["Engines"].push_back(planes->at(getPlaneIndex(planeID)).getEngines()[j].getEnginePosition());

            cout << "Engine " << planes->at(getPlaneIndex(planeID)).
                                 getEngines()[j].getEnginePosition() << " is Damaged !!" << endl;

          }
        }
      }

    }
    else
    {
      int faultyParts[2];   // 2 of 4 engines
      getFaultyParts(2, faultyParts, 0, 3);   // random 2 engines are inspected to be damaged

      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < planes->at(getPlaneIndex(planeID)).getEngines().size(); ++j) {
          if( faultyParts[i] == j )
          {
            planes->at(getPlaneIndex(planeID)).getEngines()[j].setEngineCondition(true);
            temporaryRecord["Engines"].push_back(planes->at(getPlaneIndex(planeID)).getEngines()[j].getEnginePosition());

            cout << "Engine " << planes->at(getPlaneIndex(planeID)).
                                 getEngines()[j].getEnginePosition() << " is Damaged !!" << endl;
          }
        }
      }

    }

  }

}

void AirplaneMaintenance ::inspectEmpennage(const string &planeID) {

  int x;
  cout << "[1] Defects found ?" << endl << "[0] Inspection positive ?" << endl;
  cin >> x;

  if(x)
  {
    planes->at(getPlaneIndex(planeID)).setPlaneAvailability(false); // detection of defects makes plane unavailable

    // 0 for rudders, while 1 for elevator

    int faultyParts[1];   // either rudders or elevator
    getFaultyParts(1, faultyParts, 0, 1);   // randomly inspects rudders or elevator to be damaged

    if(faultyParts[0])
    {
      planes->at(getPlaneIndex(planeID)).getEmpennage().setElevatorCondition(true);
      cout << "Elevator Damaged !!" << endl;
      temporaryRecord["Empennage"]["Elevator"];
      temporaryRecord["Empennage"]["Elevator"] = "X";
    }
    else
    {
      planes->at(getPlaneIndex(planeID)).getEmpennage().setRuddersCondition(true);
      cout << "Rudders Damaged !!" << endl;
      temporaryRecord["Empennage"]["Rudders"];
      temporaryRecord["Empennage"]["Rudders"] = "X";
    }

  }
}

void AirplaneMaintenance ::inspectMainLandingGears(const string &planeID) {
  int x;
  cout << "[1] Defects found ?" << endl << "[0] Inspection positive ?" << endl;
  cin >> x;

  if(x)
  {
    planes->at(getPlaneIndex(planeID)).setPlaneAvailability(false); // detection of defects makes plane unavailable

    if( planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_120" )
    {
      int faultyParts[2];   // 2 of 4 tyres and struts
      getFaultyParts(2, faultyParts, 0, 3);   // random 2 tyres and struts are inspected to be damaged

      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
          if( faultyParts[i] == j )
          {
            // Damage a strut and a tyre of left main landing gear
            planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getTyres()[j].setTyreCondition(true);
            planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getStruts()[j].setStrutCondition(true);

            // update temporary maintenance record
            temporaryRecord["MainLandingGear"]["LeftLandingGear"]["Tyres"].push_back
                (planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getTyres()[j].getTyrePos());

            temporaryRecord["MainLandingGear"]["LeftLandingGear"]["Struts"].push_back
                (planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getStruts()[j].getStrutPos());

            // display the damaged tyres and struts
            cout << "Left Landing Gear's Strut : "
                 << planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getStruts()[j].getStrutPos()
                 << " , and Tyre : "
                 << planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getTyres()[j].getTyrePos()
                 << " are Damaged !!" << endl;

            // Damage a strut and a tyre of right main landing gear
            planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getTyres()[j].setTyreCondition(true);
            planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getStruts()[j].setStrutCondition(true);

            // update temporary maintenance record
            temporaryRecord["MainLandingGear"]["RightLandingGear"]["Tyres"].push_back
                (planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getTyres()[j].getTyrePos());

            temporaryRecord["MainLandingGear"]["RightLandingGear"]["Struts"].push_back
                (planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getStruts()[j].getStrutPos());

            // display the damaged tyres and struts
            cout << "Right Landing Gear's Strut : "
                 << planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getStruts()[j].getStrutPos()
                 << " , and Tyre : "
                 << planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getTyres()[j].getTyrePos()
                 << " are Damaged !!" << endl;
          }
        }
        cout << endl;
      }

    }
    else if( planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_210"
             || planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_Cargo" )
    {
      int faultyParts[4];   // 4 of 8 tyres and struts
      getFaultyParts(4, faultyParts, 0, 7);   // random 4 tyres and struts are inspected to be damaged

      for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
          if( faultyParts[i] == j )
          {
            // Damage a strut and a tyre of left main landing gear
            planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getTyres()[j].setTyreCondition(true);
            planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getStruts()[j].setStrutCondition(true);

            // update temporary maintenance record
            temporaryRecord["MainLandingGear"]["LeftLandingGear"]["Tyres"].push_back
                (planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getTyres()[j].getTyrePos());

            temporaryRecord["MainLandingGear"]["LeftLandingGear"]["Struts"].push_back
                (planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getStruts()[j].getStrutPos());

            // display the damaged tyres and struts
            cout << "Left Landing Gear's Strut : "
                 << planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getStruts()[j].getStrutPos()
                 << " , and Tyre : "
                 << planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getTyres()[j].getTyrePos()
                 << " are Damaged !!" << endl;

            // Damage a strut and a tyre of right main landing gear
            planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getTyres()[j].setTyreCondition(true);
            planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getStruts()[j].setStrutCondition(true);

            // update temporary maintenance record
            temporaryRecord["MainLandingGear"]["RightLandingGear"]["Tyres"].push_back
                (planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getTyres()[j].getTyrePos());

            temporaryRecord["MainLandingGear"]["RightLandingGear"]["Struts"].push_back
                (planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getStruts()[j].getStrutPos());

            // display the damaged tyres and struts
            cout << "Right Landing Gear's Strut : "
                 << planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getStruts()[j].getStrutPos()
                 << " , and Tyre : "
                 << planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getTyres()[j].getTyrePos()
                 << " are Damaged !!" << endl;


          }
        }
        cout << endl;
      }

    }
    else if( planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_400" )
    {
      int faultyParts[6];   // 6 of 12 tyres and struts
      getFaultyParts(6, faultyParts, 0, 11);   // random 6 tyres and struts are inspected to be damaged

      for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 12; ++j) {
          if( faultyParts[i] == j )
          {
            // Damage a strut and a tyre of left main landing gear
            planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getTyres()[j].setTyreCondition(true);
            planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getStruts()[j].setStrutCondition(true);

            // update temporary maintenance record
            temporaryRecord["MainLandingGear"]["LeftLandingGear"]["Tyres"].push_back
                (planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getTyres()[j].getTyrePos());

            temporaryRecord["MainLandingGear"]["LeftLandingGear"]["Struts"].push_back
                (planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getStruts()[j].getStrutPos());

            // display the damaged tyres and struts
            cout << "Left Landing Gear's Strut : "
                 << planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getStruts()[j].getStrutPos()
                 << " , and Tyre : "
                 << planes->at(getPlaneIndex(planeID)).getMainLandingGear()[0].getTyres()[j].getTyrePos()
                 << " are Damaged !!" << endl;

            // Damage a strut and a tyre of right main landing gear
            planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getTyres()[j].setTyreCondition(true);
            planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getStruts()[j].setStrutCondition(true);

            // update temporary maintenance record
            temporaryRecord["MainLandingGear"]["RightLandingGear"]["Tyres"].push_back
                (planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getTyres()[j].getTyrePos());

            temporaryRecord["MainLandingGear"]["RightLandingGear"]["Struts"].push_back
                (planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getStruts()[j].getStrutPos());

            // display the damaged tyres and struts
            cout << "Right Landing Gear's Strut : "
                 << planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getStruts()[j].getStrutPos()
                 << " , and Tyre : "
                 << planes->at(getPlaneIndex(planeID)).getMainLandingGear()[1].getTyres()[j].getTyrePos()
                 << " are Damaged !!" << endl;
          }
        }
        cout << endl;
      }

    }
  }
}

void AirplaneMaintenance ::inspectNoseLandingGear(const string &planeID)
{
  int x;
  cout << "[1] Defects found ?" << endl << "[0] Inspection positive ?" << endl;
  cin >> x;

  if(x)
  {
    planes->at(getPlaneIndex(planeID)).setPlaneAvailability(false); // detection of defects makes plane unavailable

    // 0 for left tyre and strut, while 1 for right

    int faultyParts[1];   // Left or Right set of tyres and struts
    getFaultyParts(1, faultyParts, 0, 1);   // random 1 set of tyre and strut are inspected to be damaged

    if(faultyParts[0])  // Right Tyre and Strut
    {
      planes->at(getPlaneIndex(planeID)).getNoseLandingGear().getTyres()[1].setTyreCondition(true);
      planes->at(getPlaneIndex(planeID)).getNoseLandingGear().getStruts()[1].setStrutCondition(true);

      // update temporary maintenance record
      temporaryRecord["NoseLandingGear"]["Tyres"].push_back
          (planes->at(getPlaneIndex(planeID)).getNoseLandingGear().getTyres()[1].getTyrePos());

      temporaryRecord["NoseLandingGear"]["Struts"].push_back
          (planes->at(getPlaneIndex(planeID)).getNoseLandingGear().getStruts()[1].getStrutPos());

      // display the damaged tyres and struts
      cout << "Nose Landing Gear's Tyre : "
           << planes->at(getPlaneIndex(planeID)).getNoseLandingGear().getTyres()[1].getTyrePos()
           << " , and Strut : "
           << planes->at(getPlaneIndex(planeID)).getNoseLandingGear().getStruts()[1].getStrutPos()
           << " are Damaged !!" << endl;
    }
    else  // Left Tyre and Strut
    {
      planes->at(getPlaneIndex(planeID)).getNoseLandingGear().getTyres()[0].setTyreCondition(true);
      planes->at(getPlaneIndex(planeID)).getNoseLandingGear().getStruts()[0].setStrutCondition(true);

      // update temporary maintenance record
      temporaryRecord["NoseLandingGear"]["Tyres"].push_back
          (planes->at(getPlaneIndex(planeID)).getNoseLandingGear().getTyres()[0].getTyrePos());

      temporaryRecord["NoseLandingGear"]["Struts"].push_back
          (planes->at(getPlaneIndex(planeID)).getNoseLandingGear().getStruts()[0].getStrutPos());

      cout << "Nose Landing Gear's Tyre : "
           << planes->at(getPlaneIndex(planeID)).getNoseLandingGear().getTyres()[0].getTyrePos()
           << " , and Strut : "
           << planes->at(getPlaneIndex(planeID)).getNoseLandingGear().getStruts()[0].getStrutPos()
           << " are Damaged !!" << endl;
    }
    cout << endl;
  }
}

void AirplaneMaintenance ::inspectWindows(const string &planeID)
{
  int x;
  cout << "[1] Defects found ?" << endl << "[0] Inspection positive ?" << endl;
  cin >> x;

  if(x)
  {
    planes->at(getPlaneIndex(planeID)).setPlaneAvailability(false); // detection of defects makes plane unavailable

    if(planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_120")
    {
      int faultyParts[4];   // 4 of 20 windows on left as well as right side
      getFaultyParts(4, faultyParts, 0, 19);   // random 4 windows on either side inspected to be damaged

      for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 20; ++j) {
          if( faultyParts[i] == j )
          {
            planes->at(getPlaneIndex(planeID)).getWindows(0)[j].setWindowCondition(true);
            planes->at(getPlaneIndex(planeID)).getWindows(1)[j].setWindowCondition(true);

            // update temporary maintenance record

            temporaryRecord["Windows"].push_back(planes->at(getPlaneIndex(planeID)).getWindows(0)[j].getWindowID());
            temporaryRecord["Windows"].push_back(planes->at(getPlaneIndex(planeID)).getWindows(1)[j].getWindowID());

            cout << " Left Side's Window : "
                 << planes->at(getPlaneIndex(planeID)).getWindows(0)[j].getWindowID()
                 << " , and Right Side's Window : "
                 << planes->at(getPlaneIndex(planeID)).getWindows(1)[j].getWindowID()
                 << " are cracked !!" << endl;
          }
        }
      }
    }
    else if(planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_210")
    {
      int faultyParts[6];   // 6 of 30 windows on left side while 4 of 20 windows  on right side
      getFaultyParts(6, faultyParts, 0, 29);   // random 4 windows on either side inspected to be damaged

      for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 30; ++j) {
          if( faultyParts[i] == j )
          {
            planes->at(getPlaneIndex(planeID)).getWindows(0)[j].setWindowCondition(true);
            planes->at(getPlaneIndex(planeID)).getWindows(1)[j].setWindowCondition(true);

            // update temporary maintenance record

            temporaryRecord["Windows"].push_back(planes->at(getPlaneIndex(planeID)).getWindows(0)[j].getWindowID());
            temporaryRecord["Windows"].push_back(planes->at(getPlaneIndex(planeID)).getWindows(1)[j].getWindowID());

            cout << " Left Side's Window : "
                 << planes->at(getPlaneIndex(planeID)).getWindows(0)[j].getWindowID()
                 << " , and Right Side's Window : "
                 << planes->at(getPlaneIndex(planeID)).getWindows(1)[j].getWindowID()
                 << " are cracked !!" << endl;
          }
        }
      }
    }
    else if(planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_400")
    {
      int faultyParts[8];   // 8 of 40 windows on left side while 4 of 20 windows  on right side
      getFaultyParts(8, faultyParts, 0, 39);   // random 4 windows on either side inspected to be damaged

      for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 40; ++j) {
          if( faultyParts[i] == j )
          {
            planes->at(getPlaneIndex(planeID)).getWindows(0)[j].setWindowCondition(true);
            planes->at(getPlaneIndex(planeID)).getWindows(1)[j].setWindowCondition(true);

            // update temporary maintenance record

            temporaryRecord["Windows"].push_back(planes->at(getPlaneIndex(planeID)).getWindows(0)[j].getWindowID());
            temporaryRecord["Windows"].push_back(planes->at(getPlaneIndex(planeID)).getWindows(1)[j].getWindowID());

            cout << " Left Side's Window : "
                 << planes->at(getPlaneIndex(planeID)).getWindows(0)[j].getWindowID()
                 << " , and Right Side's Window : "
                 << planes->at(getPlaneIndex(planeID)).getWindows(1)[j].getWindowID()
                 << " are cracked !!" << endl;
          }
        }
      }
    }
  }

}

void AirplaneMaintenance ::inspectSeats(const string &planeID)
{
  int x;
  cout << "[1] Defects found ?" << endl << "[0] Inspection positive ?" << endl;
  cin >> x;

  if(x)
  {
    planes->at(getPlaneIndex(planeID)).setPlaneAvailability(false); // detection of defects makes plane unavailable

    if(planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_120")
    {
      // Randomly inspect 10 seats to be damaged

      int faultyRows[5];   // 5 of 20 rows of plane will have some seats damaged
      getFaultyParts(5, faultyRows, 0, 19);   // randomly inspects 5 rows having damaged seats
      int faultySeatsinRows[2];   // 2 of 6 columns in a row will be damaged
      getFaultyParts(2, faultySeatsinRows, 0, 5);   // randomly inspects 2 seats to be damaged

      for (int i = 0; i < 5; ++i)
      {
        for (int j = 0; j < 20; ++j)   // 20 rows in AirTaxi_120 planes
        {
          if( faultyRows[i] == j )
          {
            for (int k = 0; k < 2; ++k)
            {
              for (int l = 0; l < 6; ++l)   // 6 columns in AirTaxi_120 planes
              {
                if( faultySeatsinRows[k] == l )
                {
                  planes->at(getPlaneIndex(planeID)).getPlaneSeats()[j][l]->setAvailability(false);

                  // update temporary maintenance record

                  temporaryRecord["Seats"].push_back(planes->at(getPlaneIndex(planeID)).getPlaneSeats()[j][l]->getSeatID());

                  cout << planes->at(getPlaneIndex(planeID)).getPlaneID()
                       << " SEAT : " << planes->at(getPlaneIndex(planeID)).getPlaneSeats()[j][l]->getSeatID()
                       << " Damaged !!" << endl;
                }
              }
            }
          }
        }
        cout << endl;
      }

    }
    else if(planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_210")
    {
      int faultyRows[8];   // 8 of 30 rows of plane will have some seats damaged
      getFaultyParts(8, faultyRows, 0, 29);   // randomly inspects 8 rows having damaged seats
      int faultySeatsinRows[3];   // 3 of 7 columns in a row will be damaged
      getFaultyParts(3, faultySeatsinRows, 0, 6);   // randomly inspects 3 seats to be damaged

      for (int i = 0; i < 8; ++i)
      {
        for (int j = 0; j < 30; ++j)   // 30 rows in AirTaxi_210 planes
        {
          if( faultyRows[i] == j )
          {
            for (int k = 0; k < 3; ++k)
            {
              for (int l = 0; l < 7; ++l)   // 7 columns in AirTaxi_210 planes
              {
                if( faultySeatsinRows[k] == l )
                {
                  planes->at(getPlaneIndex(planeID)).getPlaneSeats()[j][l]->setAvailability(false);

                  // update temporary maintenance record

                  temporaryRecord["Seats"].push_back(planes->at(getPlaneIndex(planeID)).getPlaneSeats()[j][l]->getSeatID());

                  cout << planes->at(getPlaneIndex(planeID)).getPlaneID()
                       << " SEAT : " << planes->at(getPlaneIndex(planeID)).getPlaneSeats()[j][l]->getSeatID()
                       << " Damaged !!" << endl;
                }
              }
            }
          }
        }
        cout << endl;
      }
    }
    else if(planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_400")
    {
      int faultyRows[10];   // 5 of 20 rows of plane will have some seats damaged
      getFaultyParts(10, faultyRows, 0, 39);   // randomly inspects 5 rows having damaged seats
      int faultySeatsinRows[4];   // 2 of 6 rows in a column will be damaged
      getFaultyParts(4, faultySeatsinRows, 0, 9);   // randomly inspects 4 seats to be damaged

      for (int i = 0; i < 10; ++i)
      {
        for (int j = 0; j < 40; ++j)   // 40 rows in AirTaxi_400 planes
        {
          if( faultyRows[i] == j )
          {
            for (int k = 0; k < 4; ++k)
            {
              for (int l = 0; l < 10; ++l)   // 10 columns in AirTaxi_400 planes
              {
                if( faultySeatsinRows[k] == l )
                {
                  planes->at(getPlaneIndex(planeID)).getPlaneSeats()[j][l]->setAvailability(false);

                  // update temporary maintenance record

                  temporaryRecord["Seats"].push_back(planes->at(getPlaneIndex(planeID)).getPlaneSeats()[j][l]->getSeatID());

                  cout << planes->at(getPlaneIndex(planeID)).getPlaneID()
                       << " SEAT : " << planes->at(getPlaneIndex(planeID)).getPlaneSeats()[j][l]->getSeatID()
                       << " Damaged !!" << endl;
                }
              }
            }
          }
        }
        cout << endl;
      }
    }
  }
}

void AirplaneMaintenance ::inspectWings(const string &planeID)
{
  int x;
  cout << "[1] Defects found ?" << endl << "[0] Inspection positive ?" << endl;
  cin >> x;

  if(x)
  {
    planes->at(getPlaneIndex(planeID)).setPlaneAvailability(false); // detection of defects makes plane unavailable

    // randomly inspect 2 parts from either wing to be damaged

    int faultyWing[1];
    getFaultyParts(1, faultyWing, 0, 1);
    int faultyParts[2];
    getFaultyParts(2, faultyParts, 0, 4);

    if(faultyWing[0])
    {
      temporaryRecord["RightWing"];

      for (int i = 0; i < 2; ++i) {
        if( faultyParts[i] == 0 )
        {
          planes->at(getPlaneIndex(planeID)).getWings()->setFlaps(true);
          temporaryRecord["RightWing"]["Flaps"] = "X";
          cout << "Right Wing Flaps Damaged !!" << endl;
        }
        else if( faultyParts[i] == 1 )
        {
          planes->at(getPlaneIndex(planeID)).getWings()->setSlats(true);
          temporaryRecord["RightWing"]["Slats"] = "X";
          cout << "Right Wing Slats Damaged !!" << endl;
        }
        else if( faultyParts[i] == 2 )
        {
          planes->at(getPlaneIndex(planeID)).getWings()->setWinglet(true);
          temporaryRecord["RightWing"]["Winglet"] = "X";
          cout << "Right Wing Winglet Damaged !!" << endl;
        }
        else if( faultyParts[i] == 3 )
        {
          planes->at(getPlaneIndex(planeID)).getWings()->setAileron(true);
          temporaryRecord["RightWing"]["Aileron"] = "X";
          cout << "Right Wing Aileron Damaged !!" << endl;
        }
        else if( faultyParts[i] == 4 )
        {
          planes->at(getPlaneIndex(planeID)).getWings()->setSpoiler(true);
          temporaryRecord["RightWing"]["Spoiler"] = "X";
          cout << "Right Wing Spoiler Damaged !!" << endl;
        }
      }
    }
    else
    {
      temporaryRecord["LeftWing"];

      for (int i = 0; i < 2; ++i) {
        if( faultyParts[i] == 0 )
        {
          planes->at(getPlaneIndex(planeID)).getWings()->setFlaps(true);
          temporaryRecord["LeftWing"]["Flaps"] = "X";
          cout << "Left Wing Flaps Damaged !!" << endl;
        }
        else if( faultyParts[i] == 1 )
        {
          planes->at(getPlaneIndex(planeID)).getWings()->setSlats(true);
          temporaryRecord["LeftWing"]["Slats"] = "X";
          cout << "Left Wing Slats Damaged !!" << endl;
        }
        else if( faultyParts[i] == 2 )
        {
          planes->at(getPlaneIndex(planeID)).getWings()->setWinglet(true);
          temporaryRecord["LeftWing"]["Winglet"] = "X";
          cout << "Left Wing Winglet Damaged !!" << endl;
        }
        else if( faultyParts[i] == 3 )
        {
          planes->at(getPlaneIndex(planeID)).getWings()->setAileron(true);
          temporaryRecord["LeftWing"]["Aileron"] = "X";
          cout << "Left Wing Aileron Damaged !!" << endl;
        }
        else if( faultyParts[i] == 4 )
        {
          planes->at(getPlaneIndex(planeID)).getWings()->setSpoiler(true);
          temporaryRecord["LeftWing"]["Spoiler"] = "X";
          cout << "Left Wing Spoiler Damaged !!" << endl;
        }
      }
    }

  }
}

void AirplaneMaintenance ::inspectAirplane( const string & planeID ) {

  int n;

  if( !planes->at(getPlaneIndex(planeID)).isPlaneAvailable() )
  {
    cout << "!! Cannot inspect an already unavailable plane !!" << endl;
    cout << " !! Pay off Maintenance Costs for Plane first !!" << endl;
    return;
  }

  cout << endl;

  json tasked_employees;

  if( checkForEmployees() )
  {
    tasked_employees = assignEmployees();  // get data of assigned employees
  }
  else
    return;

  cout << "!! AIRPLANE " << planeID << " INSPECTION STARTED !!" << endl;

  // read record into the planes json variable
  planes->at(getPlaneIndex(planeID)).readMaintenanceRecord();

  vector<string> inspectionOptions;

  inspectionOptions.resize(7);
  inspectionOptions[0] = "[1] Inspect Airplane Engine";
  inspectionOptions[1] = "[2] Inspect Airplane Empennage";
  inspectionOptions[2] = "[3] Inspect Airplane LandingGears";
  inspectionOptions[3] = "[4] Inspect Airplane Seats";
  inspectionOptions[4] = "[5] Inspect Airplane Windows";
  inspectionOptions[5] = "[6] Inspect Airplane Wings";
  inspectionOptions[6] = "[7] Exit Inspection" ;

  vector <int> optionCheck;

  while(true)
  {
    // iterate through the available options
    for (const auto& option : inspectionOptions) {
      cout << option << endl;
    }

    cin >> n;

    if (n < 1 || n > 7) {
      cout << "Invalid input. Please enter a number between 1 and 7." << endl;
      continue; // Skip to next iteration
    }

    if (n == 7) {
      break; // Exit loop
    }

    bool check = true;
    for (int i = 0; i < optionCheck.size(); ++i) {
      if( optionCheck[i] == n ){
        cout << "This Inspection has already been made !!" << endl;
        check = false;
      }
    }
    if(!check) continue;

    optionCheck.push_back(n);

    switch (n)
    {
    case 1:
      cout << setw(8) << "--- INSPECTING AIRPLANE ENGINES ---" << endl;
      inspectEngines(planeID);
      break;
    case 2:
      cout << setw(8) << "--- INSPECTING AIRPLANE EMPENNAGE ---" << endl;
      inspectEmpennage(planeID);
      break;
    case 3:
      cout << setw(8) << "--- INSPECTING MAIN LANDING GEARS ---" << endl;
      inspectMainLandingGears(planeID);
      cout << setw(8) << "--- INSPECTING NOSE LANDING GEAR  ---" << endl;
      inspectNoseLandingGear(planeID);
      break;
    case 4:
      cout << setw(8) << "--- INSPECTING AIRPLANE SEATS  ---" << endl;
      inspectSeats(planeID);
      break;
    case 5:
      cout << setw(8) << "--- INSPECTING AIRPLANE WINDOWS  ---" << endl;
      inspectWindows(planeID);
      break;
    case 6:
      cout << setw(8) << "--- INSPECTING AIRPLANE WINGS  ---" << endl;
      inspectWings(planeID);
      break;
    }

  }

  writeLandedPlanes(planeID,"remove");

  if(!planes->at(getPlaneIndex(planeID)).isPlaneAvailable())
  {
    temporaryRecord["isAvailable"];
    temporaryRecord["isAvailable"] = false;

    temporaryRecord["assignedEmployees"];
    temporaryRecord["assignedEmployees"] = tasked_employees;

    planes->at(getPlaneIndex(planeID)).getPlaneMaintenanceRecord().push_back(temporaryRecord);
    temporaryRecord.clear();

    planes->at(getPlaneIndex(planeID)).editMaintenanceRecord();
    planes->at(getPlaneIndex(planeID)).readMaintenanceRecord();

    bool choice;

    do {
      cout << endl <<  "Make repairs ? " << endl << "[1] YES " << endl << "[0] NO " << endl;
      cin >> choice;
    } while ( choice != 1 && choice != 0 );

    if(!choice)
    {
      cout << "Airplane is no more available for flights. " << endl;
      cout << "    !! Pay off bills for repairs !!"          << endl;
      return;
    }

    generateBills(planeID);
  }

}

void AirplaneMaintenance ::displayUnavailablePlanes() {

  int x;
  bool check = true;

  while(true)
  {
    for (int i = 0; i < planes->size(); ++i) {
      if( !planes->at(i).isPlaneAvailable() )
      {
        cout << "[" << i + 1 << "] " << planes->at(i).getPlaneID() << endl;
        check = false;
      }
    }

    if(check)
    {
      cout << "!! NO UNAVAILABLE AIRPLANES !!" << endl;
      return;
    }

    cout << "Enter corresponding number for plane inspection" << endl;
    cout << "Enter -1 to Exit" << endl;
    cin >> x;

    cout << endl;

    if( x == -1 )
      return;

    generateBills(planes->at(x-1).getPlaneID());
  }

}

void AirplaneMaintenance ::writeLandedPlanes( const string & planeID, const string & action ) {

  json landedPlanes = readLandedPlanes();

//  if (landedPlanes.empty())
//    landedPlanes.clear();   // could be containing null

  if( action == "remove")
  {
    for (int i = 0; i < landedPlanes.size(); ++i) {
      if ( landedPlanes[i] == planeID )
        landedPlanes.erase( landedPlanes.begin() + i );
    }
  }
  else if(action == "add")
    landedPlanes.push_back(planeID);

  cout << landedPlanes;

   string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e"  //JAMZEE
                     "\\LandedPlanes\\LandedPlanes.json";
// string filepath = "C:\\Users\\Scorp Radoz\\OneDrive\\Documents\\GitHub\\old\\2024-Spring-SE102TB-Project-se102b-e \\LandedPlanes\\LandedPlanes.json"; //Samers's
//  string filepath = ("C:\\Users\\User\\OneDrive\\Desktop\\PROJECT\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\PlaneCosts.json");

  ofstream outFile(filepath, ios ::trunc);
  outFile << landedPlanes;
  outFile.close();
}

json AirplaneMaintenance ::readLandedPlanes() {

  json landedPlanes;

  string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e"   //jamzeeeeeeeee
                    "\\LandedPlanes\\LandedPlanes.json";
//    string filepath = " C:\\Users\\Scorp Radoz\\OneDrive\\Documents\\GitHub\\old\\2024-Spring-SE102TB-Project-se102b-e\\LandedPlanes\\LandedPlanes.json";
    ifstream inFile(filepath);
  if (!inFile.is_open())
    return json ::array();   // In case no planes have yet landed
  inFile >> landedPlanes;
  inFile.close();

  return landedPlanes;

}

bool AirplaneMaintenance ::checkLandedPlanesFile(const string &planeID) {

  json landedPlanes = readLandedPlanes();

  for (int j = 0; j < landedPlanes.size(); ++j) {
    if( landedPlanes[j] == planeID )
      return true;
  }

  return false;   // no planes with planeID exist in file
}

void AirplaneMaintenance ::displayLandedPlanes() {

  json landedPlanes = readLandedPlanes();

  string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e"   //jamzerewr
                    "\\LandedPlanes\\LandedPlanes.json";
//    string filepath = " C:\\Users\\Scorp Radoz\\OneDrive\\Documents\\GitHub\\old\\2024-Spring-SE102TB-Project-se102b-e\\LandedPlanes\\LandedPlanes.json";  //samer

  int num;

  bool check = true;

  while(true)
  {
    for (int i = 0; i < planes->size(); ++i) {
      if (checkLandedPlanesFile( planes->at(i).getPlaneID())){
        check = false;
        cout << "[" << i + 1 << "] " << planes->at(i).getPlaneID() << "   ** NOT INSPECTED YET ** " << endl;
      }
    }

    if(check)
    {
      cout << "!! NO LANDED PLANES FOR INSPECTION !!" << endl;
      return;
    }

    if ( landedPlanes.size() != 0 )
    {
      cout << "Enter corresponding no. for plane inspection" << endl;
      cout << "Enter -1 to Exit" << endl;
      cin >> num;

      cout << endl;

      if( num == -1 )
        return;

      inspectAirplane(planes->at(num-1).getPlaneID());
    }
    else
    {
      cout << "** NO LANDED PLANES FOR INSPECTION **" << endl;
      return;
    }

    landedPlanes = readLandedPlanes();

  }

}

void AirplaneMaintenance ::displayAvailablePlanes() {

  int num;

  json landedPlanes = readLandedPlanes();

  bool check = true;

  for (int i = 0; i < planes->size(); ++i) {
    if( planes->at(i).isPlaneAvailable() )
    {
      check = false;

      if( checkLandedPlanesFile(planes->at(i).getPlaneID()) )
        cout << "[" << i + 1 << "] " << planes->at(i).getPlaneID() << "   ** NOT INSPECTED YET ** " << endl;
      else if( planes->at(i).getFlightStatus() )
        cout << "[" << i + 1 << "] " << planes->at(i).getPlaneID() << "   ** IN FLIGHT **" << endl;
      else
        cout << "[" << i + 1 << "] " << planes->at(i).getPlaneID() << endl;

    }
  }

  if(check)
  {
    cout << "!! NO AVAILABLE AIRPLANES !!" << endl;
    return;
  }

}

void AirplaneMaintenance ::generateBills(const string &planeID) {

  double total = 0.0;
  int type;

  readPlaneCosts();   // read plane costs from file into json variable
  planes->at(getPlaneIndex(planeID)).readMaintenanceRecord();   // read maintenance record into variable

  // fetch the latest record of plane
  int index = planes->at(getPlaneIndex(planeID)).getPlaneMaintenanceRecord().size() - 1;
  json record_holder = planes->at(getPlaneIndex(planeID)).getPlaneMaintenanceRecord()[index];

  if( planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_120" )
    type = 0;
  else if( planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_210" )
    type = 1;
  else if( planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_400" )
    type = 2;
  else if( planes->at(getPlaneIndex(planeID)).getPlaneType() == "AirTaxi_Cargo" )
    type = 3;

  if( !record_holder["Engines"].empty() )
  {
    cout << "--- ENGINE BILLS ---" << endl;
    for (int i = 0; i < record_holder["Engines"].size(); ++i) {
      cout << "Engine " << record_holder["Engines"][i] << " : " << planeCosts[type]["Engine"] << endl;
      total += (double)planeCosts[type]["Engine"];
    }
  }
  else
    cout << "NO BILLS FOR ENGINES !!" << endl;


  if( record_holder["Empennage"]["Elevator"] == nullptr && record_holder["Empennage"]["Rudders"] == nullptr )
    cout << "NO BILLS FOR EMPENNAGE !!" << endl;
  else
  {
    if( record_holder["Empennage"]["Elevator"] == "X" )
    {
      cout << "--- ELEVATOR'S BILLS ---" << endl;
      cout << "Elevator : " << planeCosts[type]["Empennage"]["Elevator"] << endl;
      total += (double)planeCosts[type]["Empennage"]["Elevator"];
    }
    else if( record_holder["Empennage"]["Rudders"] == "X" )
    {
      cout << "--- RUDDER'S  BILLS ---" << endl;

      cout << "Rudders : " << planeCosts[type]["Empennage"]["Rudders"] << endl;
      total += (double)planeCosts[type]["Empennage"]["Rudders"];
    }
  }


  if( record_holder["MainLandingGear"]["RightLandingGear"]["Tyres"].empty() )
    cout << "NO BILLS FOR MAIN LANDING GEARS !!" << endl;
  else
  {
    cout << "--- LEFT LANDING GEAR ---" << endl;
    for (int i = 0; i < record_holder["MainLandingGear"]["LeftLandingGear"]["Tyres"].size(); ++i) {

      cout << "Tyre " << record_holder["MainLandingGear"]["LeftLandingGear"]["Tyres"][i]
           << " : " << planeCosts[type]["LandingGear"]["MainLandingGear"]["Tyre"] << endl;

      total += (double)planeCosts[type]["LandingGear"]["MainLandingGear"]["Tyre"];

      cout << "Strut " << record_holder["MainLandingGear"]["LeftLandingGear"]["Struts"][i]
           << " : " << planeCosts[type]["LandingGear"]["MainLandingGear"]["Strut"] << endl;

      total += (double)planeCosts[type]["LandingGear"]["MainLandingGear"]["Strut"];
    }

    cout << "--- RIGHT LANDING GEAR ---" << endl;
    for (int i = 0; i < record_holder["MainLandingGear"]["RightLandingGear"]["Tyres"].size(); ++i) {

      cout << "Tyre " << record_holder["MainLandingGear"]["RightLandingGear"]["Tyres"][i]
           << " : " << planeCosts[type]["LandingGear"]["MainLandingGear"]["Tyre"] << endl;

      total += (double)planeCosts[type]["LandingGear"]["MainLandingGear"]["Tyre"];

      cout << "Strut " << record_holder["MainLandingGear"]["RightLandingGear"]["Struts"][i]
           << " : " << planeCosts[type]["LandingGear"]["MainLandingGear"]["Strut"] << endl;

      total += (double)planeCosts[type]["LandingGear"]["MainLandingGear"]["Strut"];
    }
  }

  if( record_holder["NoseLandingGear"]["Tyres"].empty() )
    cout << "NO BILLS FOR NOSE LANDING GEAR !!" << endl;
  else
  {
    cout << "--- NOSE LANDING GEAR ---" << endl;
    for (int i = 0; i < record_holder["NoseLandingGear"]["Tyres"].size(); ++i) {

      cout << "Tyre " << record_holder["NoseLandingGear"]["Tyres"][i]
           << " : " << planeCosts[type]["LandingGear"]["NoseLandingGear"]["Tyre"] << endl;

      total += (double)planeCosts[type]["LandingGear"]["NoseLandingGear"]["Tyre"];

      cout << "Strut " << record_holder["NoseLandingGear"]["Struts"][i]
           << " : " << planeCosts[type]["LandingGear"]["NoseLandingGear"]["Strut"] << endl;

      total += (double)planeCosts[type]["LandingGear"]["NoseLandingGear"]["Strut"];
    }
  }

  if( record_holder.contains("RightWing") )
  {
    cout << "--- RIGHT WING PARTS BILLS ---" << endl;
    for ( json ::iterator it = record_holder["RightWing"].begin(); it != record_holder["RightWing"].end(); it++ )
    {
      if( it.key() == "Flaps" )
      {
        cout << "Flaps : " << planeCosts[type]["Wings"]["Flaps"] << endl;
        total += (double) planeCosts[type]["Wings"]["Flaps"];
      }
      else if( it.key() == "Slats" )
      {
        cout << "Slats : " << planeCosts[type]["Wings"]["Slats"] << endl;
        total += (double) planeCosts[type]["Wings"]["Slats"];
      }
      else if( it.key() == "Winglet" )
      {
        cout << "Winglet : " << planeCosts[type]["Wings"]["Winglet"] << endl;
        total += (double) planeCosts[type]["Wings"]["Winglet"];
      }
      else if( it.key() == "Aileron" )
      {
        cout << "Aileron : " << planeCosts[type]["Wings"]["Aileron"] << endl;
        total += (double) planeCosts[type]["Wings"]["Aileron"];
      }
      else if( it.key() == "Spoiler" )
      {
        cout << "Spoiler : " << planeCosts[type]["Wings"]["Spoiler"] << endl;
        total += (double) planeCosts[type]["Wings"]["Spoiler"];
      }
    }
  }
  else if( record_holder.contains("LeftWing") )
  {
    cout << "--- LEFT WING PARTS BILLS ---" << endl;
    for ( json ::iterator it = record_holder["LeftWing"].begin(); it != record_holder["LeftWing"].end(); it++ )
    {
      if( it.key() == "Flaps" )
      {
        cout << "Flaps : " << planeCosts[type]["Wings"]["Flaps"] << endl;
        total += (double) planeCosts[type]["Wings"]["Flaps"];
      }
      else if( it.key() == "Slats" )
      {
        cout << "Slats : " << planeCosts[type]["Wings"]["Slats"] << endl;
        total += (double) planeCosts[type]["Wings"]["Slats"];
      }
      else if( it.key() == "Winglet" )
      {
        cout << "Winglet : " << planeCosts[type]["Wings"]["Winglet"] << endl;
        total += (double) planeCosts[type]["Wings"]["Winglet"];
      }
      else if( it.key() == "Aileron" )
      {
        cout << "Aileron : " << planeCosts[type]["Wings"]["Aileron"] << endl;
        total += (double) planeCosts[type]["Wings"]["Aileron"];
      }
      else if( it.key() == "Spoiler" )
      {
        cout << "Spoiler : " << planeCosts[type]["Wings"]["Spoiler"] << endl;
        total += (double) planeCosts[type]["Wings"]["Spoiler"];
      }
    }
  }
  else
    cout << "NO BILLS FOR EITHER OF THE WINGS !!" << endl;


  if( type != 3 )   // if PlaneType is not Cargo Plane
  {
    if( !record_holder["Seats"].empty() )
    {
      cout << "--- PLANE SEATS BILLS ---" << endl;
      for (int i = 0; i < record_holder["Seats"].size(); ++i) {
        cout << "Seat " << record_holder["Seats"][i] << " : "
             << planeCosts[type]["PassengerCompartment"]["Seat"] << endl;
        total += (double) planeCosts[type]["PassengerCompartment"]["Seat"];
      }
    }
    else
      cout << "NO BILLS FOR SEATS !!" << endl;

    if( !record_holder["Windows"].empty() )
    {
      cout << "--- PLANE WINDOW BILLS ---" << endl;
      for (int i = 0; i < record_holder["Windows"].size(); ++i) {
        cout << "Window " << record_holder["Windows"][i] << " : "
             << planeCosts[type]["PassengerCompartment"]["Window"] << endl;
        total += (double) planeCosts[type]["PassengerCompartment"]["Window"];
      }
    }
    else
      cout << "NO BILLS FOR WINDOWS !!" << endl;
  }

  if( total > 0 )
  {
    cout << "!!! TOTAL BILL FOR MAINTENANCE : " << total << " !!!" << endl;

    bool choice;

    cout << "[1] Pay Bills ?" << endl << "[0] Skip Payment " << endl;
    cin >> choice;

    if(!choice)
    {
      cout << "Plane wont be available until repairs are made !!" << endl;
      return;
    }

    // Deduction from Budget here //

    if(AirplaneMaintenanceAccount.addBalanceUnknownAcc("company123",total,"Plane maintainance"))
    {
      planes->at(getPlaneIndex(planeID)).setPlaneAvailability(true);
      planes->at(getPlaneIndex(planeID)).getPlaneMaintenanceRecord()[index]["isAvailable"] = true;
      planes->at(getPlaneIndex(planeID)).editMaintenanceRecord();

      planes->at(getPlaneIndex(planeID)).setPlaneAvailability(true);
      planes->at(getPlaneIndex(planeID)).getPlaneMaintenanceRecord()[index]["isAvailable"] = true;
      planes->at(getPlaneIndex(planeID)).editMaintenanceRecord();
      cout << "A Total of " << total << " pkr has been successfully paid !!" << endl;
    }
    else return;  // If budget is not enough
  }
}

bool AirplaneMaintenance ::checkForEmployees() {

  int InspectionManagersCount = 0;
  int TechniciansCount = 0;

  for (int i = 0; i < employees->size(); ++i) {

    if( employees->at(i)->getDesignation() == "InspectionManager" )
      InspectionManagersCount += 1;
    if( employees->at(i)->getDesignation() == "Technician" )
      TechniciansCount += 1;
  }

  if( InspectionManagersCount >= 1 && TechniciansCount >= 3 )
    return true;

  cout << "       !!   NOT ENOUGH EMPLOYEES FOR OPERATION   !!" << endl;
  cout << "***  AN INSPECTION MANAGER & 3 TECHNICIANS REQUIRED  ***" << endl;
  return false;

}

json AirplaneMaintenance::assignEmployees()
{
  vector<Employee**> ref_employees;

  for (int i = 0; i < employees->size(); ++i) {
    if (employees->at(i)->getDesignation() == "InspectionManager" ||
        employees->at(i)->getDesignation() == "Technician") {
      ref_employees.push_back(&(*employees)[i]);
    }
  }

  cout << " ***  AVAILABLE EMPLOYEES  *** " << endl;
  for (int i = 0; i < ref_employees.size(); ++i) {
    cout << "[" << i + 1 << "] " << (*ref_employees[i])->getId()
         << " --- " << (*ref_employees[i])->getDesignation() << endl;
  }
  cout << endl;

  int x;
  int IMCount = 0;
  int TCount = 0;

  json employees_list;

  set<int> input_history;

  do {
    do {
      cout << endl;
      cout << "Assign an InspectionManager and 3 Technicians for this task" << endl;
      cin >> x;
    } while (!(x >= 1 && x <= ref_employees.size()));

    if (input_history.count(x) == 0) {
      input_history.insert(x);

      if ((*ref_employees[x - 1])->getDesignation() == "InspectionManager") {
        if (IMCount < 1) {
          employees_list.push_back({{"ID", (*ref_employees[x - 1])->getId()}, {"ROLE", (*ref_employees[x - 1])->getDesignation()}});
          IMCount += 1;
        } else {
          cout << "!! ONLY 1 INSPECTION MANAGER CAN BE ASSIGNED !!" << endl;
        }
      }

      if ((*ref_employees[x - 1])->getDesignation() == "Technician") {
        if (TCount < 3) {
          employees_list.push_back({{"ID", (*ref_employees[x - 1])->getId()}, {"ROLE", (*ref_employees[x - 1])->getDesignation()}});
          TCount += 1;
        } else {
          cout << "!! NO MORE THAN 3 TECHNICIANS CAN BE ASSIGNED !!" << endl;
        }
      }
    } else {
      cout << "!! EMPLOYEE : " << (*ref_employees[x - 1])->getId() << " ALREADY ASSIGNED !!" << endl;
    }

    if (IMCount == 1 && TCount == 3) {
      break;
    }
  } while (true);

  return employees_list;
}

void AirplaneMaintenance ::displaySeatsInfo() {

  cout << "\t\t-- DISPLAY SEATS INFO -- " << endl << endl;

  int input;

  while(true)
  {
    for (int i = 0; i < planes->size(); ++i) {
      cout << "\t\t[" << i + 1 << "] " << planes->at(i).getPlaneID() << endl;
    }
    cout << "\t\t[-1] Exit" << endl;

    cin >> input;

    if( input == -1 )
      break;

    int choice;

    if( input > 0 && input <= planes->size())
    {
      if( planes->at(input-1).getPlaneType() != "AirTaxi_Cargo" )
      {

        while(true)
        {
          cout << "\t\t-- DISPLAY BY TYPE -- " << endl;
          cout << "\t\t[1] Premium Class" << endl;
          cout << "\t\t[2] Preferred Class" << endl;
          cout << "\t\t[3] Extra LegRoom Class" << endl;
          cout << "\t\t[4] Standard Class" << endl;
          cout << "\t\t[-1] Exit" << endl;
          cin >> choice;

          if( choice == -1 )
            break;

          if( choice > 0 && choice <= 4)
          {
            if( choice == 1 )
              dynamic_cast<PassengerFuselage*>(planes->at(input-1).getFuselage())
                  ->getPassengerCompartment().displaySeatsDescription<PremiumSeat>();
            else if( choice == 2 )
              dynamic_cast<PassengerFuselage*>(planes->at(input-1).getFuselage())
                  ->getPassengerCompartment().displaySeatsDescription<PreferredSeat>();
            else if( choice == 3 )
              dynamic_cast<PassengerFuselage*>(planes->at(input-1).getFuselage())
                  ->getPassengerCompartment().displaySeatsDescription<LegRoomSeat>();
            else if( choice == 4 )
              dynamic_cast<PassengerFuselage*>(planes->at(input-1).getFuselage())
                  ->getPassengerCompartment().displaySeatsDescription<StandardSeat>();
          }
        }
      }
    }

  }


}

void AirplaneMaintenance ::maintenanceMenu()
{

  int x;

  while(true)
  {
    system("clear");
    cout << endl;
    cout << " \t\t [1] Display & Inspect Landed Planes" << endl;
    cout << " \t\t [2] Pay Bills for Unavailable Planes" << endl;
    cout << " \t\t [3] Display Available Planes" << endl;
    cout << " \t\t [4] View Airplanes Costs" << endl;
    cout << " \t\t [5] View Airplanes' Status" << endl;
    cout << " \t\t [6] View Airplane Seats Info" << endl;
    cout << " \t\t [7] Exit" << endl;

    do{
      cin >> x;
      cout << endl;
    }while( !(x >= 1 && x <= 7) );

    if ( x == 1 )
    {
      displayLandedPlanes();
    }
    else if ( x == 2 )
    {
      displayUnavailablePlanes();
    }
    else if ( x == 3 )
    {
      displayAvailablePlanes();
    }
    else if ( x == 4 )
    {
      displayPlaneCosts();
    }
    else if( x == 5 )
    {
      string input;

      while(true)
      {

        for (int i = 0; i < planes->size(); ++i) {
          cout << "[" << i + 1 << "] " << planes->at(i).getPlaneID() << endl;
        }
        cout << "[" << planes->size() + 1 << "] EXIT" << endl;

        getline(cin, input);

        if( input == to_string(planes->size() + 1) )
          break;

        if ( choiceChecker(input,1,planes->size()) != "ERROR" )
        {
          for (int i = 0; i < planes->size(); ++i) {
            if( i + 1 == stoi(input) )
            {
              planes->at(i).displayAirplaneStatus();
            }
          }
        }
        else cout << "!! Invalid Input !!" << endl;

      }

    }
    else if( x == 6 )
    {
      displaySeatsInfo();
    }
    else if ( x == 7 )
    {
      return;
    }
  }

}