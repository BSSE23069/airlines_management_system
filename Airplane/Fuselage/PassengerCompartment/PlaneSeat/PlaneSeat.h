//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_PLANESEAT_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_PLANESEAT_H

#include <iostream>
#include "ctime"
using namespace std;

class PlaneSeat {
private:
  string seatID;
  bool isAvailable;
  bool isBooked;
  time_t timeOfBooking;
  bool isWindow;
  double legRoom;

protected:
  double price;   // Samer data member

public:
  PlaneSeat(string ID, bool window, double space);
  virtual ~PlaneSeat() {}   // delete derived classes
  string getSeatID() const;
  bool isWindowSeat() const;
  bool getIsAvailable() const;
  void setAvailability( bool value );
  virtual void displayDescription() const;

  virtual void setPrice(double hours)=0;   // Samer Function
  double getPrice();   // Samer Function
  bool isSeatBooked();
  void setBooking( bool value );
};

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_PLANESEAT_H
