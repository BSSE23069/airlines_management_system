//
// Created by jammy on 06/04/2024.
//

#include "Empennage.h"

Empennage::Empennage(bool rudders, bool elevators) {
  isElevator = elevators;
  isRudder = rudders;
}

void Empennage ::setElevatorCondition(bool value) {
  isElevator = value;
}

void Empennage ::setRuddersCondition(bool value) {
  isRudder = value;
}

bool Empennage::isElevatorDamaged() const{
  return isElevator;
}

bool Empennage::isRuddersDamaged() const{
  return isRudder;
}