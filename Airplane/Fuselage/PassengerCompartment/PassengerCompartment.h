//
// Created by jammy on 06/04/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_PASSENGERCOMPARTMENT_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_PASSENGERCOMPARTMENT_H

#include <iostream>
#include <vector>
#include<iomanip>
using namespace std;

#include "OverHeadBin/OverHeadBin.h"
#include "Window/Window.h"
#include "PlaneSeat/PlaneSeat.h"
#include "PlaneSeat/PremiumSeat.h"
#include "PlaneSeat/PreferredSeat.h"
#include "PlaneSeat/LegRoomSeat.h"
#include "PlaneSeat/StandardSeat.h"

class PassengerCompartment {
private:
  vector<vector<PlaneSeat*>> seats;
  int totalSeats;
  vector<Window> windows[2];
  int totalWindows;
  //  vector<OverHeadBin> overHeadBins[2];
  //  int totalOverHeadBins{};

  int totalRows;
  int totalColumns;
  int aisles;

  int seatsRows[4];
  int seatsSpace[4];

public:
  PassengerCompartment( int aisles, int rows, int columns, int seatsRows[], int seatsSpace[] );
  ~PassengerCompartment();

  void setSeats();
  void setWindows();
  //  void setCabins();


  template <class T>
  void displaySeatsDescription() {
    cout << "\t\t   *********************************************************************" << endl;
    for (int i = 0; i < totalRows; ++i) {
      for (int j = 0; j < totalColumns; ++j) {
        T* seat = dynamic_cast<T*>(seats[i][j]);
        if (seat) {
          cout << "\t\t";
          seat->displayDescription();
        }
      }
    }
    cout << "\t\t   *********************************************************************" << endl;
  }

  friend ostream& operator<<(ostream& out, const PassengerCompartment& object);

  // setter
  void setWindowAvailability( const string &ID, bool value );
  void setSeatAvailability( const string &ID, bool value );
  void setSeatBooking( const string &ID, bool value );

  // getters
  vector <Window> & getWindows( int column );
  vector < vector <PlaneSeat*> > &getSeats();


  void setPrice(double hours);   // Samer Function

  double getSeatPrice(string ID);   // Samer function
};

inline ostream& operator <<(ostream& out, const PassengerCompartment& object){

  out << setw(28) << "--- SEAT ORIENTATION ---" << endl << endl;
  out << setw(26) << "--- Premium Class ---" << endl;

  for (int i = 0; i < object.seatsRows[0]; ++i) {
    for (int j = 0; j < object.totalColumns; ++j) {
      if( !object.seats[i][j]->isSeatBooked() )
        out << setw(5) <<  object.seats[i][j]->getSeatID();
      else
        cout << setw(5) << "*";

    }
    out << endl;
  }

  out << setw(28) << "--- Preferred Class ---" << endl;
  for (int i = object.seatsRows[0]; i < object.seatsRows[0] + object.seatsRows[1]; ++i) {
    for (int j = 0; j < object.totalColumns; ++j) {
      if( !object.seats[i][j]->isSeatBooked() )
        out << setw(5) <<  object.seats[i][j]->getSeatID();
      else
        cout << setw(5) << "*";
    }
    out << endl;
  }
  out << setw(30) << "--- Extra Legroom Class ---" << endl;
  for (int i = object.seatsRows[0] + object.seatsRows[1]; i < object.seatsRows[0] + object.seatsRows[1] + object.seatsRows[2]; ++i) {
    for (int j = 0; j < object.totalColumns; ++j) {
      if( !object.seats[i][j]->isSeatBooked() )
        out << setw(5) <<  object.seats[i][j]->getSeatID();
      else
        cout << setw(5) << "*";
    }
    out << endl;
  }
  out << setw(26) << "--- Standard Class ---" << endl;
  for (int i = object.seatsRows[0] + object.seatsRows[1] + object.seatsRows[2]; i < object.seatsRows[0] + object.seatsRows[1] + object.seatsRows[2] + object.seatsRows[3]; ++i) {
    for (int j = 0; j < object.totalColumns; ++j) {
      if( !object.seats[i][j]->isSeatBooked() )
        out << setw(5) <<  object.seats[i][j]->getSeatID();
      else
        cout << setw(5) << "*";
    }
    out << endl;
  }
  out << endl;

  return out;
}

#endif // INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_PASSENGERCOMPARTMENT_H
