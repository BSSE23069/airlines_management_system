//
// Created by lenovo on 4/19/2024.
//

#include "Courier.h"
//constructor
Courier::Courier()  {
    name="";
    available= false;
    age=0;
   a1=new Account[100];
    id=0;
    employeeCount=0;
}
Courier* Courier::instance = nullptr;

Courier* Courier::getInstance() {
    if(!instance) {
        instance = new Courier;
    }
    return instance;
}
nlohmann::json Courier::employeeRead(){
    ifstream in("CargoDepartment.json");
    nlohmann::json n;
    if(!in.is_open()) {
        cout<<"error";
    }
    in >> n;
    in.close();
    return n;
}
nlohmann::json Courier::readCourier()
{
    ifstream in("courier.json", std::ios::in);
    nlohmann::json n;
    if(!in.is_open()){
        cerr<<"error"<<endl;
    }
    in>>n;
    in.close();
    return n;

}
// function to add employee
void Courier::addEmployee(nlohmann::json &dep) {
    time_t now = time(nullptr);
    dep=employeeRead();
    tm *ti = localtime(&now);
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter age: ";
    std::cin >> age;
    std::cout << "Enter id: ";
    std::cin >> id;
    std::cout << "Enter salary: ";
    std::cin >> salary;
    std::cout << "Enter account number: ";
    std::cin >> accountNo;
    nlohmann::json cargo;
    cargo["name"] = name;
    cargo["age"] = age;
    cargo["id"] = id;
    cargo["accountNo"] = accountNo;
    cargo["salary"] = salary;
    cargo["available"] = available;
    dep["CargoEmployee"].push_back(cargo);

    std::ofstream out("CargoDepartment.json");
    out << dep;
    out.close();
    employeeCount++;
}
//function to remove employee by its id in integers
void Courier:: removeEmployee(nlohmann::json &dep) {
    dep=employeeRead();
    int idToRemove;
    std::cout << "Enter the ID of the employee to remove: ";
    std::cin >> idToRemove;
    for (int it=0; it < dep["CargoEmployee"].size(); ++it) {
        if (dep["CargoEmployee"][it]["id"] == idToRemove) {
            dep["CargoEmployee"].erase(it);
            std::cout << "Employee with ID " << idToRemove << " has been removed.\n";
            employeeCount--;
            return;
        }
    }
    std::cout << "Employee with ID " << idToRemove << " not found.\n";
}
//function to display employee
void Courier::displayEmployee(nlohmann::json &dep) {
    dep=employeeRead();
    std::cout << "Employee Details:\n";
    for (const auto &employee: dep["CargoEmployee"]) {
        std::cout << "Name: " << employee["name"] << std::endl;
        std::cout << "Age: " << employee["age"] << std::endl;
        std::cout << "ID: " << employee["id"] << std::endl;
        std::cout << "Salary: " << employee["salary"] << std::endl;
        std::cout << "Join Date: " << employee["join date"] << std::endl;
        std::cout << "-----------------------\n";
    }
}
//function to mark attendance
void Courier::attendance(nlohmann::json &dep, int day, string names) {
       dep=employeeRead();
    time_t now = time(nullptr);
    tm *ti = localtime(&now);
    int currentMonth = ti->tm_mon ;
    int currentYear = ti->tm_year ;

    for (int i = 0; i < dep["CargoEmployee"].size(); i++) {
        cout<<names;
        
        if (dep["CargoEmployee"][i]["name"] == names) {
        cout<<names;
            dep["CargoEmployee"][i]["attendance"][currentYear][currentMonth][day] = "Present";
            dep["CargoEmployee"][i]["workingDays"] = +1;
        } else {
            dep["CargoEmployee"][i]["attendance"][currentYear][currentMonth][day] = "absent";
        }
    }
}
//function to deduct salary
void Courier::deductSalary(nlohmann::json &dep, int year, int month) {
       dep=employeeRead();
    for (int i = 0; i < dep["CargoEmployee"].size(); i++) {
        int absentDays = 0;
        int workingDays = dep["CargoEmployee"][i]["workingDays"];

        if (dep["CargoEmployee"][i]["attendance"].find(std::to_string(year)) !=
            dep["CargoEmployee"][i]["attendance"].end() &&
            dep["CargoEmployee"][i]["attendance"][std::to_string(year)].find(std::to_string(month)) !=
            dep["CargoEmployee"][i]["attendance"][std::to_string(year)].end()) {

            auto &attendance = dep["CargoEmployee"][i]["attendance"][std::to_string(year)][std::to_string(month)];
            for (auto it = attendance.begin(); it != attendance.end(); ++it) {
                auto &value = it.value();
                if (value == "Absent") {
                    absentDays++;
                }
            }

            double salaryEmployee = dep["CargoEmployee"][i]["salary"];
            double dailySalary = salaryEmployee / workingDays;
            double deduction = absentDays * dailySalary;
            salaryEmployee -= deduction;
            a1->addBalance(salaryEmployee, "cargo");
            dep["CargoEmployee"][i]["salary"] = salaryEmployee;
        }
    }
}

 //start flight
 void Courier::startFlight(vector<Airplane> &airplanes, int num) {
    cout << airplanes[num].getPlaneID() << endl;
     airplanes[num].setFlightStatus(true);
 }
 //end flight
 void Courier::endFlight(AirplaneMaintenance &airplaneMaintenance, vector<Airplane> &airplanes) {

     json planes;

     ifstream inFile(R"(C:\OOPS_PROJECT_EXTENDED\2024-Spring-SE102TB-Project-se102b-e\FlightStatus\FlightStatus.json)");
     if(!inFile.is_open())
     {
        cout << "!! ERROR OPENING LANDED PLANES FILE  !!" << endl;
        return;
     }
     inFile >> planes;
     inFile.close();

     int num;
     cout << "  *** ENTER NUM TO SELECT AIRPLANE *** " << endl;
     for (int i = 0; i < planes.size() ; ++i) {
       cout << "    [" << i << "] " << planes[i] << endl;
     }
     cin >> num;


     for (int i = 0; i < airplanes.size(); ++i) {
       if ( planes[num] == airplanes[i].getPlaneID() )
       {
            airplaneMaintenance.writeLandedPlanes(planes[num],"add");
            airplanes[i].setFlightStatus(false);
            cout << " *** FLIGHT SUCCESSFULLY ENDED *** "  << endl;
            return;
       }
     }

 }

//display available plane and send items into it and make record
  nlohmann::json Courier:: planeRead(){
    ifstream in ("cargoPlane.json");
    nlohmann::json n;
    if(!in.is_open()){
       cerr<<"error";
    }
    in>>n;
    in.close();
    return n;
}

void Courier ::setCourier(AirplaneMaintenance & airplaneMaintenance, vector<Airplane> & airplanes, const string &planeID) {

    double totalWeight = 0.0;
    int count;
    string itemId;
    double weight;
    nlohmann::json cargoPlane;
    nlohmann::json courier = readCourier();

    // Loop through sender entries in courier.json
    for (int i = 0; i < courier["sender"].size(); i++) {
       if (courier["sender"][i]["sending status"] == false) {
            // Iterate over each item in the sender's data
            for (int j = 0; j < courier["sender"][i]["no of items"].size(); j++) {
                // Extract id and weight for each item
                itemId = courier["sender"][i]["id"][j];
                weight = courier["sender"][i]["weight"][j];
                // Check if adding this item exceeds total weight limit
                if (totalWeight + weight <= 1000) {
                    totalWeight += weight;
                    // Create a JSON object for the item and add it to cargoPlane
                    nlohmann::json item;
                    item["id"] = itemId;
                    item["weight"] = weight;
                    item["status"]=false;
                    item["planeId"]=planeID;
                    cargoPlane["items"].push_back(item);


                } else {
                    // If adding this item exceeds weight limit, exit loop
                    break;
                }
            }
       }
    }

    int x;

    for (int i = 0; i < airplanes.size(); ++i) {
      if( airplanes[i].getPlaneID() == planeID )
       {
            x = i;
            break;
      }
    }

    // Write cargoPlane to cargoPlane.json file

    startFlight(airplanes, x);

    std::ofstream outFile("cargoPlane.json");
    outFile << cargoPlane; // Pretty print with indentation
    outFile.close();

}

void Courier::displayCargoPlanes(AirplaneMaintenance &airplaneMaintenance, vector<Airplane> &airplanes) {


    int x;

    while(true)
    {
       airplaneMaintenance.displayAvailablePlanes();

       cout << "[-1] Exit" << endl;
       cin >> x;

       if( x == -1 )
            return;

       if( airplanes[x-1].getPlaneType() == "AirTaxi_Cargo")
       {
            setCourier(airplaneMaintenance, airplanes, airplanes[x-1].getPlaneID());
            break;
       }
       else
       {
            cout << "!! Passenger Airplanes cannot be assigned for Cargo !!" << endl;
       }
    }



}

