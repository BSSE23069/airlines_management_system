//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_WING_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_WING_H

#include <iostream>
using namespace std;

class Wing {
private:
  string wingPosition;
  bool isFlaps;
  bool isSlats;
  bool isWinglet;
  bool isAileron;
  bool isSpoiler;

public:
  Wing(string pos, bool slats, bool flaps, bool winglet, bool aileron, bool spoiler);
  // setters
  void setFlaps( bool value );
  void setSlats( bool value );
  void setWinglet( bool value );
  void setAileron( bool value );
  void setSpoiler( bool value );
  // getters
  bool getFlaps() const;
  bool getSlats() const;
  bool getWinglet() const;
  bool getAileron() const;
  bool getSpoiler() const;
};

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_WING_H
