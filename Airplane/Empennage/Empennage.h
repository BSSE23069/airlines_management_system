//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_EMPENNAGE_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_EMPENNAGE_H

#include <iostream>
using namespace std;

class Empennage {
private:
  bool isElevator;
  bool isRudder;

public:
  Empennage(bool rudders, bool elevators);

  void setElevatorCondition( bool value );
  void setRuddersCondition( bool value );

  bool isElevatorDamaged() const;
  bool isRuddersDamaged() const;
};

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_EMPENNAGE_H
