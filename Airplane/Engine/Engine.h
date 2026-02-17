//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_ENGINE_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_ENGINE_H

#include <iostream>
using namespace std;

class Engine {
private:
  string enginePosition;
  bool isDamaged;

public:
  Engine(string pos);
  string getEnginePosition() const;
  void setEngineCondition( bool value );
  bool isEngineDamaged() const;
};

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_ENGINE_H
