//
// Created by jammy on 06/04/2024.
//

#include "LegRoomSeat.h"

LegRoomSeat::LegRoomSeat(string ID, bool window, double space)
    : PlaneSeat(ID, window, space), type("LegRoomSeat") {}

void LegRoomSeat::displayDescription() const{
  cout << "Type : " << type << ", ";
  PlaneSeat::displayDescription();
}

void LegRoomSeat::setPrice(double hours) {
  price=hours*40000;  // 40k pkr/hr
}