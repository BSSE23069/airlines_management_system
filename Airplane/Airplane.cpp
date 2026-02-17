//
// Created by jammy on 19/04/2024.
//

#include "Airplane.h"

int Airplane ::increment = 1;

Airplane ::Airplane(const string & planeType, int engines, int aisles, int rows, int cols)
    : planeID( planeType + "_" + to_string(increment++) ), planeType(planeType),
      empennage(false, false), wings{ Wing("L",false,false,false,false,false), Wing("R",false,false,false,false,false) },
      mainLandingGear{LandingGear(false,false), LandingGear{false,false}}, noseLandingGear(false,false)
// initializing landing gears with zero
{
  planeMaintenanceRecord =  json ::array();
  readMaintenanceRecord();

  isFlight = false;
  isAvailable = true;

  if( engines == 4 )   // medium and long haul planes
  {
    this->engines.emplace_back("LW2");   // 4 engines, and their positions
    this->engines.emplace_back("LW1");
    this->engines.emplace_back("RW1");
    this->engines.emplace_back("RW2");

    if( this->planeType == "AirTaxi_400"){
      mainLandingGear[0] = LandingGear(12, 12);   // 12 tyres, 12 struts
      mainLandingGear[1] = LandingGear(12, 12);
    }
    else if( this->planeType == "AirTaxi_210"){
      mainLandingGear[0] = LandingGear(8, 8);   // 8 tyres, 8 struts
      mainLandingGear[1] = LandingGear(8, 8);
    }
  }

  else if( engines == 2 )   // short haul planes
  {
    this->engines.emplace_back("LW");   // 2 engines, and their positions
    this->engines.emplace_back("RW");

    mainLandingGear[0] = LandingGear(4, 4);   // 4 tyres, 4 struts
    mainLandingGear[1] = LandingGear(4, 4);
  }

  noseLandingGear = LandingGear(2, 2);   // nose landing gear is same for all types

  int seatRows[4];
  int seatSpaces[4] = {34, 32, 38, 30};

  if( planeType == "AirTaxi_120")   // short haul aircraft
  {
    seatRows[0] = 4;
    seatRows[1] = 6;
    seatRows[2] = 2;
    seatRows[3] = 8;

    fuselage = new PassengerFuselage( aisles, rows, cols, seatRows, seatSpaces );
  }
  else if( planeType == "AirTaxi_210")   // medium haul aircraft
  {
    seatRows[0] = 6;
    seatRows[1] = 10;
    seatRows[2] = 4;
    seatRows[3] = 10;
    fuselage = new PassengerFuselage( aisles, rows, cols, seatRows, seatSpaces );
  }
  else if( planeType == "AirTaxi_400")   // long haul aircraft
  {
    seatRows[0] = 8;
    seatRows[1] = 12;
    seatRows[2] = 4;
    seatRows[3] = 16;
    fuselage = new PassengerFuselage( aisles, rows, cols, seatRows, seatSpaces );
  }

  bookedSeats = json ::array();
  readBookedSeats();

}

Airplane ::Airplane(int capacity, json & items)
    : planeID( "AirTaxi_Cargo_" + to_string(increment++) ), planeType("AirTaxi_Cargo"),
      empennage(false, false), wings{ Wing("L",false,false,false,false,false), Wing("R",false,false,false,false,false) },
      mainLandingGear{LandingGear(false,false), LandingGear{false,false}}, noseLandingGear(false,false)

// initializing landing gears with zero
{
  planeMaintenanceRecord = json ::array();
  readMaintenanceRecord();

  isFlight = false;
  isAvailable = true;

  // setting up positions for engines
  this->engines.emplace_back("LW2");
  this->engines.emplace_back("LW1");
  this->engines.emplace_back("RW1");
  this->engines.emplace_back("RW2");

  // 2 main landing gears, each 8 tyres, and 8 struts
  mainLandingGear[0] = LandingGear(8, 8);
  mainLandingGear[1] = LandingGear(8, 8);

  // 1 nose landing gear, having 2 tyres, and 2 struts
  noseLandingGear = LandingGear(2, 2);

  // setting up cargo fuselage, having a cargo compartment
  fuselage = new CargoFuselage(capacity, items);
}


string Airplane ::getPlaneID() {
  return planeID;
}

string Airplane ::getPlaneType() {
  return planeType;
}

void Airplane ::setPlaneAvailability(bool value) {

  isAvailable = value;

  bool setValue;

  if(value)
    setValue = false;

  // set Engines
  for (int i = 0; i < engines.size(); ++i) {
    engines[i].setEngineCondition(setValue);
  }

  // set Empennage
  empennage.setElevatorCondition(setValue);
  empennage.setRuddersCondition(setValue);

  // set Wings
  for (int i = 0; i < 2; ++i) {
    wings[i].setFlaps(setValue); wings[i].setSlats(setValue); wings[i].setWinglet(setValue);
    wings[i].setAileron(setValue); wings[i].setSpoiler(setValue);
  }

  // set Seats and Windows
  if( planeType != "AirTaxi_Cargo" )
  {
    for (int i = 0; i < getPlaneSeats().size(); ++i){
      for (int j = 0; j < getPlaneSeats()[i].size(); ++j){
        getPlaneSeats()[i][j]->setAvailability(value);
      }
    }

    for (int i = 0; i < getWindows(0).size(); ++i) {
      getWindows(0)[i].setWindowCondition(setValue);
      getWindows(1)[i].setWindowCondition(setValue);
    }
  }

  // set Main Landing Gears
  if( planeType == "AirTaxi_120" )
  {
    for (int i = 0; i < 4; ++i) {
      mainLandingGear[0].getStruts()[i].setStrutCondition(setValue);
      mainLandingGear[0].getTyres()[i].setTyreCondition(setValue);
      mainLandingGear[1].getStruts()[i].setStrutCondition(setValue);
      mainLandingGear[1].getTyres()[i].setTyreCondition(setValue);
    }
  }
  else if( planeType == "AirTaxi_400" )
  {
    for (int i = 0; i < 12; ++i) {
      mainLandingGear[0].getStruts()[i].setStrutCondition(setValue);
      mainLandingGear[0].getTyres()[i].setTyreCondition(setValue);
      mainLandingGear[1].getStruts()[i].setStrutCondition(setValue);
      mainLandingGear[1].getTyres()[i].setTyreCondition(setValue);
    }
  }
  else
  {
    for (int i = 0; i < 8; ++i) {
      mainLandingGear[0].getStruts()[i].setStrutCondition(setValue);
      mainLandingGear[0].getTyres()[i].setTyreCondition(setValue);
      mainLandingGear[1].getStruts()[i].setStrutCondition(setValue);
      mainLandingGear[1].getTyres()[i].setTyreCondition(setValue);
    }
  }

  // set Nose Landing Gears
  for (int i = 0; i < 2; ++i){
    noseLandingGear.getTyres()[i].setTyreCondition(setValue);
    noseLandingGear.getStruts()[i].setStrutCondition(setValue);
  }


}

bool Airplane ::isPlaneAvailable() {
  return isAvailable;
}

json Airplane ::readFlightStatus() {

  string filepath = R"(C:\OOPS_PROJECT_EXTENDED\2024-Spring-SE102TB-Project-se102b-e\FlightStatus\FlightStatus.json)";
  json inFlightPlanes;

  ifstream inFile(filepath);
  if( !inFile.is_open() )
    return json ::array();
  else
    inFile >> inFlightPlanes;
  inFile.close();

  for (int i = 0; i < inFlightPlanes.size(); ++i) {
    if( inFlightPlanes[i] == planeID )
      isFlight = true;
  }

  return inFlightPlanes;

}

void Airplane ::writeFlightStatus(bool value) {

  string filepath = R"(C:\OOPS_PROJECT_EXTENDED\2024-Spring-SE102TB-Project-se102b-e\FlightStatus\FlightStatus.json)";
  json inFlightPlanes = readFlightStatus();

  if( !inFlightPlanes.empty() )
  {
    if(!value)
    {
      for (int i = 0; i < inFlightPlanes.size(); ++i) {
        if (inFlightPlanes[i] == planeID) {
          inFlightPlanes.erase(inFlightPlanes.begin() + i);
        }
      }
    }
  }
  else
    inFlightPlanes.push_back(planeID);

  ofstream outfile(filepath, ios ::trunc);
  outfile << inFlightPlanes;
  outfile.close();

}

void Airplane ::setFlightStatus(bool value) {

  if( (value && isFlight) || !(value && isFlight) )
  {
    if( isAvailable )
    {
      writeFlightStatus(value);
      isFlight = value;

      if( planeType != "AirTaxi_Cargo" )
      {
        if(!isFlight)
        {
          bookedSeats.clear();   // clear booked seats data if flight is cancelled

          for (auto & row : getPlaneSeats()) {   // unbook all seats
            for (auto & column : row) {
              column->setBooking(false);
            }
          }

        }
      }

      writeBookedSeats();
    }
    else cout << "UNAVAILABLE AIRPLANE CANNOT BE ASSIGNED A FLIGHT !!" << endl;
  }
  else cout << "!! INFLIGHT AIRPLANE CANNOT BE ASSIGNED TO ANOTHER FLIGHT !!" << endl;


}

bool Airplane ::getFlightStatus() {
  return isFlight;
}

vector<Engine> &Airplane ::getEngines() {
  return engines;
}

Empennage &Airplane ::getEmpennage() {
  return empennage;
}

LandingGear *Airplane ::getMainLandingGear() {
  return mainLandingGear;
}

LandingGear &Airplane ::getNoseLandingGear() {
  return noseLandingGear;
}

vector<Window> &Airplane ::getWindows(int column) {
  if( planeType == "AirTaxi_Cargo")
  {
    cerr << "!! Cargo planes do not have a passenger compartment !!" << endl;
    exit(0);
  }
  return dynamic_cast<PassengerFuselage*>(fuselage)->getPassengerCompartment().getWindows(column);
}

vector<vector<PlaneSeat *>> &Airplane ::getPlaneSeats() {
  if( planeType == "AirTaxi_Cargo")
  {
    cerr << "!! Cargo planes do not have a passenger compartment !!" << endl;
    exit(0);
  }
  return dynamic_cast<PassengerFuselage*>(fuselage)->getPassengerCompartment().getSeats();
}

Fuselage *Airplane ::getFuselage() {
  return fuselage;
}

Wing * Airplane ::getWings() {
  return wings;
}

json &Airplane ::getPlaneMaintenanceRecord() {
  return planeMaintenanceRecord;
}

void Airplane ::readMaintenanceRecord() {

  string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Records\\"  //JAMZEE
                    + planeID + "_maintenance_record.json";
//    string filepath = "C:\\Users\\Scorp Radoz\\OneDrive\\Documents\\GitHub\\old\\2024-Spring-SE102TB-Project-se102b-e\\Records\\"  //JAMZEE
//                 + planeID + "_maintenance_record.json" ;   //SAMER

  ifstream inFile(filepath);
  if(!inFile.is_open())
  {
    cout << "--- NO EXISTING MAINTENANCE RECORD FOR " << planeID << " ---" << endl << endl;
    return;
  }
  inFile >> planeMaintenanceRecord;
  inFile.close();
}

void Airplane ::editMaintenanceRecord() {

  string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\"
                    + planeID + "_maintenance_record.json";   //JAMZEEEE
//    string filepath = "C:\\Users\\Scorp Radoz\\OneDrive\\Documents\\GitHub\\old\\2024-Spring-SE102TB-Project-se102b-e\\Records\\"
//                      + planeID + "_maintenance_record.json";   //SAMER

  ofstream outFile(filepath, ios ::trunc );
  outFile << planeMaintenanceRecord.dump(3);
  outFile.close();
}

Airplane &Airplane ::getAirPlane() {
  return *this;
}


/* --> SAMER'S FUNCTIONALITY AHEAD <-- */

void Airplane::displaySeats() {
    fuselage->DisplaySeats();
}

void Airplane ::setSeat(const string &ID, bool value) {

  if ( isFlight )
  {
    for (int i = 0; i < getPlaneSeats().size(); ++i) {
      for (int j = 0; j < getPlaneSeats()[i].size(); ++j) {
        if ( getPlaneSeats()[i][j]->getSeatID() == ID ) {
          if(value)
          {
            if ( !getPlaneSeats()[i][j]->isSeatBooked() )
            {
              getPlaneSeats()[i][j]->setBooking(value);  // set seat as booked
              if (!bookedSeats.contains(getPlaneSeats()[i][j]->getSeatID()))  // check if seat ID is already in json array
                bookedSeats.push_back(getPlaneSeats()[i][j]->getSeatID());
            }
            else
              cout << "Seat : " << getPlaneSeats()[i][j]->getSeatID() << " already booked !!" << endl;
          }
          else
            getPlaneSeats()[i][j]->setBooking(value);  // set seat as unBooked
        }
      }
    }

    writeBookedSeats();
  }
  else cout << "AirPlane not assigned to a flight !!" << endl;

}

json &Airplane ::getBookedSeats() {
  return bookedSeats;
}

void Airplane ::readBookedSeats() {

   string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Records\\"
                     + planeID + "_booking_record.json";  //JAMZEEE
//   string filepath = R"(C:\Users\Scorp Radoz\Documents\GitHub\2024-Spring-SE102TB-Project-se102b-e\Records\)"
//                     + planeID + "_booking_record.json";   //SAMER

  ifstream  inFile(filepath);
  if(!inFile.is_open())
  {
    cout << "--- NO EXISTING BOOKING RECORD FOR " << planeID << " ---" << endl << endl;
    return;
  }
  inFile >> bookedSeats;
  inFile.close();

  if( bookedSeats.empty() )
  {
    cout << "--- AIRPLANE NOT ASSIGNED TO A FLIGHT ---" << endl;
    return;
  }

  isFlight = true;


  for (int i = 0; i < bookedSeats.size(); ++i) {;
    for (int j = 0; j < getPlaneSeats().size(); ++j) {
      for (int k = 0; k < getPlaneSeats()[j].size(); ++k) {
        if (getPlaneSeats()[j][k]->getSeatID() == bookedSeats[i]) {
          getPlaneSeats()[j][k]->setBooking(true);
        }
      }
    }
  }


}

void Airplane ::writeBookedSeats() {
//
   string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Records\\"
                     + planeID + "_booking_record.json";  //JAMZEEE
//   string filepath = R"(C:\Users\Scorp Radoz\Documents\GitHub\2024-Spring-SE102TB-Project-se102b-e\Records\)"
//                 + planeID + "_booking_record.json";    //SAMER

  ofstream outFile(filepath, ios ::trunc);
  outFile << bookedSeats.dump(3);
  outFile.close();

}

void Airplane::setSeatPrice(double &hours) {
    fuselage->setPrice(hours);
}

double Airplane::getSeatPrice(string &ID) {
    return fuselage->getPrice(ID);
}

void Airplane ::displayAirplaneStatus() {

    readMaintenanceRecord();

    if( !planeMaintenanceRecord.empty() )
    {
      int index = planeMaintenanceRecord.size() - 1;
      if( !planeMaintenanceRecord[planeMaintenanceRecord.size() - 1]["isAvailable"])
    {

        cout << "\t\t ** FAULTY PARTS **" << endl;

        if( !planeMaintenanceRecord[index]["Empennage"].empty() )
            cout << "\t\tEMPENNAGE" << endl;

        if( !planeMaintenanceRecord[index]["Engines"].empty() )
        {
            cout << "\t\tENGINES" << endl;
            for (int i = 0; i < engines.size(); ++i) {
              cout << "\t\t" << planeMaintenanceRecord[index]["Engines"][i] << endl;
            }
        }

        if( !planeMaintenanceRecord[index]["MainLandingGear"]["LeftLandingGear"]["Struts"].empty() )
        {
            cout << "\t\tLEFT LANDING GEAR " << endl;
            cout << "\t\tSTRUTS" << endl;
            for (int i = 0; i < planeMaintenanceRecord[index]["MainLandingGear"]["LeftLandingGear"]["Struts"].size(); ++i) {
              cout << "\t\t" << planeMaintenanceRecord[index]["MainLandingGear"]["LeftLandingGear"]["Struts"][i] << endl;
            }
            cout << "\t\tTYRES" << endl;
            for (int i = 0; i < planeMaintenanceRecord[index]["MainLandingGear"]["LeftLandingGear"]["Tyres"].size(); ++i) {
              cout << "\t\t" << planeMaintenanceRecord[index]["MainLandingGear"]["LeftLandingGear"]["Tyres"][i] << endl;
            }
        }

        if( !planeMaintenanceRecord[index]["MainLandingGear"]["RightLandingGear"]["Struts"].empty())
        {
            cout << "\t\tRIGHT LANDING GEAR " << endl;
            cout << "\t\tSTRUTS" << endl;
            for (int i = 0; i < planeMaintenanceRecord[index]["MainLandingGear"]["RightLandingGear"]["Struts"].size(); ++i) {
              cout << "\t\t" << planeMaintenanceRecord[index]["MainLandingGear"]["RightLandingGear"]["Struts"][i] << endl;
            }
            cout << "\t\tTYRES" << endl;
            for (int i = 0; i < planeMaintenanceRecord[index]["MainLandingGear"]["RightLandingGear"]["Tyres"].size(); ++i) {
              cout << "\t\t" << planeMaintenanceRecord[index]["MainLandingGear"]["RightLandingGear"]["Tyres"][i] << endl;
            }
        }

        if( planeMaintenanceRecord[index].contains("RightWing") )
        {
            cout << "\t\tRIGHT_WING" << endl;
            cout << "\t\t" << planeMaintenanceRecord[index]["RightWing"].dump(3) << endl;
        }
        if( planeMaintenanceRecord[index].contains("LeftWing") )
        {
            cout << "\t\tLEFT_WING" << endl;
            cout << "\t\t" << planeMaintenanceRecord[index]["LeftWing"].dump(3) << endl;
        }

        if( planeType != "AirTaxi_Cargo" )
        {
            if( !planeMaintenanceRecord[index]["Seats"].empty() )
            {
              cout << "\t\tSEATS" << endl;
              for (int i = 0; i < planeMaintenanceRecord[index]["Seats"].size(); ++i) {
                cout << "\t\t" << planeMaintenanceRecord[index]["Seats"][i] << endl;
              }
            }

            if( !planeMaintenanceRecord[index]["Windows"].empty() )
            {
              cout << "\t\tWINDOWS" << endl;
              for (int i = 0; i < planeMaintenanceRecord[index]["Windows"].size(); ++i) {
                cout << "\t\t" << planeMaintenanceRecord[index]["Windows"][i] << endl;
              }
            }
        }

    }

      return;
    }

    cout << "\t\t" << char(1) << "  NO FAULTY PARTS  " << char(1) << endl;

}