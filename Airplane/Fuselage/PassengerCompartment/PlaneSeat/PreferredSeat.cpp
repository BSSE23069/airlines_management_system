//
// Created by jammy on 06/04/2024.
//

#include "PreferredSeat.h"


PreferredSeat::PreferredSeat(string ID, bool window, double space)
    : PlaneSeat(ID, window, space), type("PreferredSeat") {

}

void PreferredSeat::displayDescription() const{
  cout << "Type : " << type << ", ";
  PlaneSeat::displayDescription();
}

void PreferredSeat::setPrice(double hours) {
  price=hours*30000;  // 30k pkr/hr
}