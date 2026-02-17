//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_CARGOFUSELAGE_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_CARGOFUSELAGE_H

#include <iostream>
using namespace std;

#include "Fuselage.h"

class CargoFuselage : public Fuselage{
  CargoCompartment cargoCompartment;

public:
  CargoFuselage( int capacity, json &items );
  CargoCompartment & getCargoCompartment();

  // useless functions
  void setSeatAvailability( const string &ID, bool value );
  void setSeatBooking( const string &ID, bool value );

  /* --> Samer Functionality <-- */
  void DisplaySeats();
  void setPrice(double hours);
  double getPrice(string ID);
};

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_CARGOFUSELAGE_H
