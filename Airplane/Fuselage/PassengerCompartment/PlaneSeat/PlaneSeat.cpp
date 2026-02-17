//
// Created by jammy on 06/04/2024.
//

#include "PlaneSeat.h"

PlaneSeat::PlaneSeat(string ID, bool window, double space)
    : seatID(ID), isWindow(window), legRoom(space) {
  isAvailable = true;
  isBooked = false;
  price = 0.0;
}

string PlaneSeat::getSeatID() const{
  return seatID;
}

bool PlaneSeat::isWindowSeat() const{
  return isWindow;
}

bool PlaneSeat::getIsAvailable() const{
  return isAvailable;
}

void PlaneSeat ::setAvailability(bool value) {
  isAvailable = value;
}

void PlaneSeat::displayDescription() const{
  cout << "ID: " << seatID << ", Window Seat: "
       << (isWindow ? "Yes" : "No") << ", Leg Room: " << legRoom
       << ", Price : " << price << " pkr/- " << endl;
}

/* -->  Samer Functionality Ahead */

double PlaneSeat::getPrice() {
  return price;
}

void PlaneSeat::setPrice(double hours) {

}

bool PlaneSeat ::isSeatBooked() {
  return isBooked;
}

void PlaneSeat ::setBooking( bool value ) {
  isBooked = value;
}