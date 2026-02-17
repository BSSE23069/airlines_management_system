//
// Created by jammy on 06/04/2024.
//

#include "Wing.h"

Wing::Wing(string pos, bool slats, bool flaps, bool winglet, bool aileron, bool spoiler) {
  wingPosition = pos;
  isFlaps = flaps;
  isSlats = slats;
  isWinglet = winglet;
  isAileron = aileron;
  isSpoiler = spoiler;
}

void Wing ::setFlaps(bool value) {
  isFlaps = value;
}

void Wing ::setSlats(bool value) {
  isSlats = value;

}

void Wing ::setWinglet(bool value) {
  isWinglet = value;
}

void Wing ::setAileron(bool value) {
  isAileron = value;
}

void Wing ::setSpoiler(bool value) {
  isSpoiler = value;
}

bool Wing::getFlaps() const{
  return isFlaps;
}

bool Wing::getSlats() const{
  return isSlats;
}

bool Wing::getWinglet() const{
  return isWinglet;
}

bool Wing::getAileron() const{
  return isAileron;
}

bool Wing::getSpoiler() const{
  return isSpoiler;
}