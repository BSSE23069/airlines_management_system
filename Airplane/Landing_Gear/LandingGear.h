//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_LANDINGGEAR_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_LANDINGGEAR_H
#include <iostream>
#include<vector>
using namespace std;

#include "Tyre.h"
#include "Strut.h"

class LandingGear {
private:
  vector<Tyre> tyres;
  int totalTyres;
  vector<Strut> struts;
  int totalStruts;

public:
  LandingGear(int tyresCount, int strutsCount);
  void setLandingGear();
  vector<Tyre> & getTyres() ;
  vector<Strut> & getStruts() ;
};


#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_LANDINGGEAR_H
