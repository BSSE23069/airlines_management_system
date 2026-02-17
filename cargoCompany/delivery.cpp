//
// Created by lenovo on 5/1/2024.
//
#include "Delivery.h"
using namespace std;
#include <iostream>
Delivery::Delivery() {
    account = "";
    balance = 0;
    petrol = 0;
    a1 = new Account[1];
    price = 0;
    distance = 0.0;
}

double Delivery::toRadians(int degrees) {
    return degrees * 3.14159265358979323846 / 180.0;
}

double Delivery::calculateDistance() {
    double lat1, lon1, lat2, lon2;
    cout << "Enter latitude of sending area: ";
    cin >> lat1;
    cout << "Enter longitude of sending area: ";
    cin >> lon1;
    cout << "Enter latitude of receiving area: ";
    cin >> lon2;
    cout << "Enter longitude of receiving area: ";
    cin >> lat2;

    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    double x = (lon2 - lon1) * cos((lat1 + lat2) / 2.0);
    double y = lat2 - lat1;
    distance = sqrt(x * x + y * y) * 6371.0;
    cout << "Distance: " << distance << endl;
    cout<<"enter price of petrol: "<<endl;
    cin>>petrol;
    price=petrol*distance;
    return distance;
}
nlohmann:: json Delivery::readCargoDepartment() {
    std::ifstream departmentFile("CargoDepartment.json");
    if (!departmentFile.is_open()) {
        std::cout << "Error opening CargoDepartment.json" << std::endl;
        return json(); // Return an empty json object if file opening fails
    }

    json cargoDepartment;
    departmentFile >> cargoDepartment;
    departmentFile.close();

    return cargoDepartment;
}

nlohmann::json Delivery::readFromCargoPlane() {
    std::ifstream planeFile("cargoPlane.json");
    if (!planeFile.is_open()) {
        std::cout << "Error opening cargoPlane.json" << std::endl;
        return json(); // Return an empty json object if file opening fails
    }

    json cargoPlane;
    planeFile >> cargoPlane;
    planeFile.close();

    return cargoPlane;
}

void Delivery::assignWorkToEmployee() {
    // Read CargoDepartment.json
    json cargoDepartment = readCargoDepartment();
    if (cargoDepartment.empty()) {
        cout << "Error reading CargoDepartment.json" << endl;
        return;
    }

    // Read cargoPlane.json
    json cargoPlane = readFromCargoPlane();
    if (cargoPlane.empty()) {
        cout << "Error reading cargoPlane.json" << endl;
        return;
    }

    // Display available employees
    cout << "Available Employees:\n";
    for (int i = 0; i < cargoDepartment["CargoEmployee"].size(); i++) {
        if (cargoDepartment["CargoEmployee"][i]["available"] == false) {
            cout << i + 1 << ". Name: " << cargoDepartment["CargoEmployee"][i]["name"] << endl;
            cout << "   ID: " << cargoDepartment["CargoEmployee"][i]["id"] << endl;
            cargoDepartment["CargoEmployee"][i]["available"] ==true;
            calculateDistance();
        }

    }

     int employeeIndex;
    cout << "Enter the corresponding number to assign work: ";
    cin >> employeeIndex;
    if (employeeIndex < 1 || employeeIndex > cargoDepartment["CargoEmployee"].size()) {
        cout << "Invalid employee index." << endl;
        return;
    }

    // Mark employee as unavailable
    cargoDepartment["CargoEmployee"][employeeIndex - 1]["available"] = false;

    // Assign work to the employee
    for (int i = 0; i < cargoPlane["items"].size(); i++) {
        if (!cargoPlane["items"][i]["status"]) {
            // Assign work to the employee
            cargoDepartment["CargoEmployee"][employeeIndex - 1]["work"].push_back(cargoPlane["items"][i]);

            // Mark the item as assigned
            cargoPlane["items"][i]["status"] = true;
        }
    }

    // Write updated cargoDepartment to file
    ofstream departmentFile("CargoDepartment.json");
    departmentFile << cargoDepartment.dump(4); // Write with indentation for readability
    departmentFile.close();

    // Write updated cargoPlane to file
    ofstream planeFile("cargoPlane.json");
    planeFile << cargoPlane.dump(4); // Write with indentation for readability
    planeFile.close();
}
