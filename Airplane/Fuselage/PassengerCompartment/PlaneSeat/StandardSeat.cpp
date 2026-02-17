//
// Created by jammy on 06/04/2024.
//

#include "StandardSeat.h"


StandardSeat::StandardSeat(string ID, bool window, double space)
    : PlaneSeat(ID, window, space), type("StandardSeat") {}

void StandardSeat::displayDescription() const {
  cout << "Type : " << type << ", ";
  PlaneSeat::displayDescription();
}

void StandardSeat::setPrice(double hours) {
    price=hours*20000;  // 20k pkr/hr
}