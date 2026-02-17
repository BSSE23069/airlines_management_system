//
// Created by jammy on 06/04/2024.
//

#include "PassengerFuselage.h"

PassengerFuselage ::PassengerFuselage(int aisles, int rows, int cols,
                                      int *seatsRows,  int *seatsSpace)
    : passengerCompartment(aisles, rows, cols, seatsRows, seatsSpace) {}

PassengerCompartment &PassengerFuselage ::getPassengerCompartment() {
  return passengerCompartment;
}

/* Samer Stuff Ahead */

void PassengerFuselage::DisplaySeats(){
  cout << passengerCompartment;
}

void PassengerFuselage::setSeatAvailability( const string &ID, bool value ){
  passengerCompartment.setSeatAvailability(ID,value);
}

void PassengerFuselage ::setSeatBooking(const string &ID, bool value) {
  passengerCompartment.setSeatBooking(ID, value);
}

void PassengerFuselage::setPrice(double hours) {
  passengerCompartment.setPrice(hours);
}

double PassengerFuselage::getPrice(std::string ID) {
  return passengerCompartment.getSeatPrice(ID);
}