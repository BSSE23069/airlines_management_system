//
// Created by jammy on 07/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_ITEM_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_ITEM_H

#include <iostream>
#include<vector>
using namespace std;

class Item{
  string itemID;
  string passengerID;
public:
  Item( const string &itemID, const string &passengerID );
  string getItemID() const;
  string getPassengerID() const;
}; // for the moment being

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_ITEM_H
