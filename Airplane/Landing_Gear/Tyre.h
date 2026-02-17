//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_TYRE_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_TYRE_H

#include <iostream>
using namespace std;

class Tyre {
private:
  string tyrePosition;
  bool isFlat;

public:
  Tyre(string pos, bool state);
  string getTyrePos() const;
  void setTyreCondition( bool value );
  bool isTyreFlat() const;
};

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_TYRE_H
