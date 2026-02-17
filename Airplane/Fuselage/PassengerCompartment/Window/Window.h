//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_WINDOW_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_WINDOW_H

#include <iostream>
using namespace std;

class Window {
private:
  string windowID;
  bool isCracked;

public:
  Window(string ID, bool state);
  string getWindowID() const;
  void setWindowCondition( bool value );
  bool isWindowCracked() const;
};


#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_WINDOW_H
