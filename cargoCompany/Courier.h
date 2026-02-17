//
// Created by lenovo on 4/19/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_COURIER_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_COURIER_H

using namespace std;
#include <iostream>
#include "json.hpp"
#include "../Accounts/Account.h"
#include "../Airplane/Airplane.h"
#include "../Departments/AirplaneMaintenance.h"
#include <fstream>
class Courier {
    int employeeCount;
    Account *a1;
    string name;
    int age;
    int salary;
    int id;
    int accountNo;
    int assign;
    bool available;
    int days;
    Courier();
   static Courier * instance;
public:
   static Courier * getInstance();
    void addEmployee(nlohmann::json &dep);
    void removeEmployee(nlohmann::json &dep);
    void displayEmployee(nlohmann::json &dep);
    void attendance(nlohmann::json &dep, int day, string names);
    void deductSalary(nlohmann::json &dep, int year, int month);
    nlohmann::json employeeRead();
    nlohmann::json readCourier();
    nlohmann::json planeRead();
    void startFlight(vector<Airplane> &airplanes, int num);
    void endFlight(AirplaneMaintenance &airplaneMaintenance, vector<Airplane> &airplanes);
    void displayCargoPlanes(AirplaneMaintenance &airplaneMaintenance, vector<Airplane> &airplanes) ;
    void setCourier( AirplaneMaintenance & airplaneMaintenance,  vector<Airplane> & airplanes,  const string & planeID );
};


#endif