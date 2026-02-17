//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_PASSENGERFUSELAGE_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_PASSENGERFUSELAGE_H

#include <iostream>
using namespace std;

#include "Fuselage.h"
#include "PassengerCompartment/PassengerCompartment.h"

class PassengerFuselage : public Fuselage{
private:
  PassengerCompartment passengerCompartment;

public:
  PassengerFuselage(int aisles, int rows, int cols,
                    int seatsRows[],  int seatsSpace[] );
  PassengerCompartment& getPassengerCompartment();

  /* --> Samer Functionality <-- */
  void setSeatAvailability( const string &ID, bool value );
  void setSeatBooking( const string &ID, bool value );
  void DisplaySeats();
  void setPrice(double hours);
  double getPrice(string ID);

};

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_PASSENGERFUSELAGE_H
