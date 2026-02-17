//
// Created by jammy on 06/04/2024.
//

#include "Tyre.h"

Tyre::Tyre(string pos, bool state) {
  tyrePosition = pos;
  isFlat = state;
}

string Tyre::getTyrePos() const{
  return tyrePosition;
}

void Tyre ::setTyreCondition(bool value) {
  isFlat = value;
}

bool Tyre::isTyreFlat() const{
  return isFlat;
}