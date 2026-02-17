//
// Created by jammy on 06/04/2024.
//

#include "PremiumSeat.h"

PremiumSeat::PremiumSeat(string ID, bool window, double space)
    : PlaneSeat(ID, window, space), type("PremiumSeat") {}

void PremiumSeat::displayDescription() const{
  cout << "Type : " << type << ", ";
  PlaneSeat::displayDescription();
}

void PremiumSeat::setPrice(double hours) {
  price=hours*50000;  // 50k pkr/hr
}



