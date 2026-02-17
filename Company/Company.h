//
// Created by jammy on 19/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_COMPANY_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_COMPANY_H

#include <iostream>
#include <vector>
using namespace std;

#include "../nlohmann/json.hpp"
#include "../Airplane/Airplane.h"
#include "../Accounts/Account.h"
#include "../ErrorHandler/ErrorHandler.h"

class Company
{
  string name;
  static Company * company;
  Account companyAccount;
  Company();
public:
  static Company * getCompany();
  void purchaseAirPlane( vector<Airplane> & planes );
  void readPlanesFile( vector<Airplane> & planes );
  void writePlanesFile( vector<Airplane> & planes );
};

//Company * Company ::company = nullptr;

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_COMPANY_H
