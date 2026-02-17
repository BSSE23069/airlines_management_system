//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_STRUT_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_STRUT_H

#include <iostream>
using namespace std;

class Strut {
private:
  string strutPosition;
  bool isDamaged;

public:
  Strut(string Pos, bool state);
  string getStrutPos() const;
  void setStrutCondition( bool value );
  bool isStrutDamaged() const;
};

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_STRUT_H
