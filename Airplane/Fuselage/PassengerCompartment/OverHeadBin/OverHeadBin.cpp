//
// Created by jammy on 06/04/2024.
//

#include "OverHeadBin.h"

OverHeadBin::OverHeadBin(string ID, int capacity)
    : overHeadID(ID), capacity(capacity), items(nullptr) {}

void OverHeadBin::setItems(vector<Item> &item) {


  // further algo to sort items in cabins

}

string OverHeadBin::getCabinID() const {
  return overHeadID;
}

int OverHeadBin::getCapacity() const {
  return capacity;
}

Item* OverHeadBin::getItems() const {
  return items;
}
