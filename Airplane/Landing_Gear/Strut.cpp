//
// Created by jammy on 06/04/2024.
//

#include "Strut.h"

Strut::Strut(string Pos, bool state) {
  strutPosition = Pos;
  isDamaged = state;
}

string Strut ::getStrutPos() const {
  return strutPosition;
}

void Strut ::setStrutCondition(bool value) {
  isDamaged = value;
}

bool Strut::isStrutDamaged() const{
  return isDamaged;
}