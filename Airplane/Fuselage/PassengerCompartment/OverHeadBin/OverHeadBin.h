//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_OVERHEADBIN_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_OVERHEADBIN_H


#include <iostream>
#include <vector>
using namespace std;

#include "../../../Item/Item.h"

class OverHeadBin {
private:
  string overHeadID;
  int capacity;
  Item* items;

public:
  OverHeadBin(string ID, int capacity);
  void setItems(vector<Item> &item);
  string getCabinID() const;
  int getCapacity() const;
  Item* getItems() const;

};

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_OVERHEADBIN_H
