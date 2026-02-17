//
// Created by jammy on 06/04/2024.
//

#include "PassengerCompartment.h"

PassengerCompartment ::PassengerCompartment( int aisles, int rows, int columns,  int *seatsRows,  int *seatsSpace )
    : aisles(aisles), totalRows(rows), totalColumns(columns), seatsRows{0,0,0,0}, seatsSpace{0,0,0,0}
// Initializing seatsRows and seatsSpaces with 0s
{
  // Use exception handling here ?

  for (int i = 0; i < 4; ++i) {
    this->seatsRows[i] = seatsRows[i];
  }

  for (int i = 0; i < 4; ++i) {
    this->seatsSpace[i] = seatsSpace[i];
  }

  totalSeats = totalRows * totalColumns;
  totalWindows = 2 * totalRows;
  //  totalOverHeadBins = 2 * totalRows;

  setSeats();   // sets the orientation of seats
  setWindows();   // sets the orientation of windows
  //  setCabins();

}

void PassengerCompartment ::setSeats() {


  string columns[10] = {"A","B","C","D","E","F","G","H","I","J"};

  seats.resize(totalRows, vector<PlaneSeat*>(totalColumns));


  // Premium Seats Orientation
  for (int i = 0; i < seatsRows[0]; ++i) {
    for (int j = 0; j < totalColumns; ++j) {
      if( j == 0 || j == totalColumns - 1 )
        seats[i][j] = new PremiumSeat(columns[j] + to_string(i), true , seatsSpace[0]);
      else
        seats[i][j] = new PremiumSeat(columns[j] + to_string(i), false , seatsSpace[0]);
    }
  }

  // Preferred Seats Orientation
  for (int i = seatsRows[0]; i < seatsRows[0] + seatsRows[1]; ++i) {
    seats.emplace_back();
    for (int j = 0; j < totalColumns; ++j) {
      if( j == 0 || j == totalColumns - 1 )
        seats[i][j] = new PreferredSeat(columns[j] + to_string(i), true , seatsSpace[1]);
      else
        seats[i][j] = new PreferredSeat(columns[j] + to_string(i), false , seatsSpace[1]);
    }
  }

  // Extra LegRoom Seats Orientation
  for (int i = seatsRows[0] + seatsRows[1]; i < seatsRows[0] + seatsRows[1] + seatsRows[2]; ++i) {
    seats.emplace_back();
    for (int j = 0; j < totalColumns; ++j) {
      if( j == 0 || j == totalColumns - 1 )
        seats[i][j] = new LegRoomSeat(columns[j] + to_string(i), true , seatsSpace[2]);
      else
        seats[i][j] = new LegRoomSeat(columns[j] + to_string(i), false , seatsSpace[2]);
    }
  }

  // Standard Seats Orientation
  for (int i = seatsRows[0] + seatsRows[1] + seatsRows[2]; i < seatsRows[0] + seatsRows[1] + seatsRows[2] + seatsRows[3]; ++i) {
    seats.emplace_back();
    for (int j = 0; j < totalColumns; ++j) {
      if( j == 0 || j == totalColumns - 1 )
        seats[i][j] = new StandardSeat(columns[j] + to_string(i), false , seatsSpace[3]);
      else
        seats[i][j] = new StandardSeat(columns[j] + to_string(i), false , seatsSpace[3]);
    }
  }

}

void PassengerCompartment ::setWindows() {

  string columns[10] = {"A","B","C","D","E","F","G","H","I","J"};

  for (int i = 0; i < totalRows; ++i) {
    windows[0].emplace_back(columns[0] + to_string(i), false);
    windows[1].emplace_back(columns[totalColumns - 1] + to_string(i), false);
  }

}

//void PassengerCompartment ::setCabins() {
//
//  string columns[10] = {"A","B","C","D","E","F","G","H","I","J"};
//
//  for (int i = 0; i < totalRows; ++i) {
//
//    if( i >= (seatsRows[0] + seatsRows[1]) && i <= (seatsRows[0] + seatsRows[1] + seatsRows[2] - 1))
//      continue;
//
//    overHeadBins[0].emplace_back(columns[0] + to_string(i), 3);
//    overHeadBins[1].emplace_back(columns[totalColumns - 1] + to_string(i), 3);
//
//  }
//}

void PassengerCompartment ::setSeatAvailability(const string &ID, bool value) {

  for (int i = 0; i < totalRows; ++i) {
    for (int j = 0; j < totalColumns; ++j) {
      if( seats[i][j]->getSeatID() == ID )
        seats[i][j]->setAvailability(value);  // set seat as available / reserved
    }
  }
}

void PassengerCompartment ::setWindowAvailability(const string &ID, bool value) {

  for (int i = 0; i < totalRows; ++i) {
    for (int j = 0; j < 2; ++j) {
      if( windows[i][j].getWindowID() == ID )
        windows[i][j].setWindowCondition(value);  // set window as damaged / fixed
    }
  }
}

void PassengerCompartment ::setSeatBooking(const string &ID, bool value) {

  for (int i = 0; i < totalRows; ++i) {
    for (int j = 0; j < 2; ++j) {
      if( seats[i][j]->getSeatID() == ID )
        seats[i][j]->setBooking(value);  // set seat as booked / not booked
    }
  }
}

vector<vector<PlaneSeat*>> &PassengerCompartment ::getSeats() {
  return seats;
}

void PassengerCompartment::setPrice(double hours) {
  for (int i = 0; i < totalRows; ++i) {
    for (int j = 0; j < totalColumns; ++j) {
      seats[i][j]->setPrice(hours);
    }
  }
}

double PassengerCompartment::getSeatPrice(std::string ID) {
  for (int i = 0; i < totalRows; ++i) {
    for (int j = 0; j < totalColumns; ++j) {
      if( seats[i][j]->getSeatID() == ID )
        return seats[i][j]->getPrice();
    }
  }
  return -1;
}

vector<Window> &PassengerCompartment ::getWindows(int column) {
  return windows[column];
}

PassengerCompartment ::~PassengerCompartment() {

  for (int i = 0; i < totalRows; ++i) {
    for (int j = 0; j < totalColumns; ++j)
      delete seats[i][j];
  }
}

