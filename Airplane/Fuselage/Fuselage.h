//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_FUSELAGE_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_FUSELAGE_H

#include <iostream>
using namespace std;

#include "../../nlohmann/json.hpp"
#include "CargoCompartment/CargoCompartment.h"

class Fuselage {
public:
  Fuselage();
  virtual ~Fuselage();
  virtual void setSeatAvailability( const string &ID, bool value );
  virtual void setSeatBooking( const string &ID, bool value );

  /* --> Samer Functionality <-- */
  virtual void DisplaySeats();
  virtual void setPrice(double hours);
  virtual double getPrice(string ID);

};

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_FUSELAGE_H
