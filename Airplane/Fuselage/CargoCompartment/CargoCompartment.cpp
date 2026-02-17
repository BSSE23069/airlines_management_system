//
// Created by jammy on 06/04/2024.
//

#include "CargoCompartment.h"

CargoCompartment ::CargoCompartment(int capacity, json &items)
    : capacity(capacity), items(items) {
}

json CargoCompartment ::getItems() const{
  return items;
}

void CargoCompartment ::setCargoCompartment(json &items) {
  this->items = items;
}


