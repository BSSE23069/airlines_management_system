//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_CARGOCOMPARTMENT_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_CARGOCOMPARTMENT_H

#include <iostream>
#include<vector>
using namespace std;

#include "../../../nlohmann/json.hpp"

#include "../../Item/Item.h"

using json = nlohmann ::json;

class CargoCompartment {
private:
  int capacity;
  json items;

public:
  CargoCompartment(int capacity, json &items);
  json getItems() const;
  void setCargoCompartment( json & items );
  friend ostream& operator << (ostream& out, const CargoCompartment& object);
};

inline ostream& operator << (ostream& out, const CargoCompartment& object){

  cout << object.items;

  for (int i = 0; i < object.getItems().size(); ++i) {
    out << "COURIER : " ;
    out << object.getItems()[i]["CourierID"] << endl;
    for (int j = 0; j < object.getItems()[i]["Items"].size(); ++j) {
      out << "ITEM [" << j + 1 << "] : ";
      out << object.getItems()[i]["Items"][j] << endl;
    }
    out << endl;
  }
  return out;

}

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_CARGOCOMPARTMENT_H
