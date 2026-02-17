#ifndef DELIVERY_H
#define DELIVERY_H

#include <iostream>
#include <fstream>
#include "json.hpp"
#include "../Accounts/Account.h"
#include <cmath>

using namespace std;
using json = nlohmann::json;

class Delivery {
private:
    string account;
    int balance;
    int petrol;
    int price;
    double distance;
   Account *a1;

public:
    Delivery();

    double toRadians(int degrees);

    double calculateDistance();

nlohmann::json readCargoDepartment() ;

nlohmann::json readFromCargoPlane();

void assignWorkToEmployee();
};

#endif // DELIVERY_H
