//
// Created by jammy on 07/04/2024.
//

#include "Item.h"

Item :: Item( const string &itemID, const string &passengerID ) : itemID(itemID), passengerID(passengerID) { }

string Item :: getItemID() const{
  return itemID;
}

string Item :: getPassengerID() const{
  return passengerID;
}