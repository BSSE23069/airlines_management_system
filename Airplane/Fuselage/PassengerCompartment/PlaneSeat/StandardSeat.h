//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_STANDARDSEAT_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_STANDARDSEAT_H


#include <iostream>
using namespace std;

#include "PlaneSeat.h"

class StandardSeat : public PlaneSeat{
public:
  string type;
  StandardSeat( string ID, bool window, double space );
  void displayDescription() const override;
  void setPrice(double hours) override;
};

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_STANDARDSEAT_H
