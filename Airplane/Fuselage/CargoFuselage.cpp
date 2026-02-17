//
// Created by jammy on 06/04/2024.
//

#include "CargoFuselage.h"

CargoFuselage ::CargoFuselage(int capacity, json &items)
    : cargoCompartment(capacity, items) {}

CargoCompartment & CargoFuselage ::getCargoCompartment() {
  return cargoCompartment;
}

void CargoFuselage ::setSeatAvailability(const std::string &ID, bool value) {
  cout << endl << "CARGO PLANE DOESNT PROVIDE THIS FUNCTIONALITY" << endl;
}

void CargoFuselage ::setSeatBooking(const std::string &ID, bool value) {
  cout << endl << "CARGO PLANE DOESNT PROVIDE THIS FUNCTIONALITY" << endl;
}

void CargoFuselage ::DisplaySeats() {
  cout << endl << "CARGO PLANE DOESNT PROVIDE THIS FUNCTIONALITY" << endl;
}

void CargoFuselage ::setPrice(double hours) {
  cout << endl << "CARGO PLANE DOESNT PROVIDE THIS FUNCTIONALITY" << endl;
}

double CargoFuselage ::getPrice(std::string ID) {
  cout << endl << "CARGO PLANE DOESNT PROVIDE THIS FUNCTIONALITY" << endl;
  return 0;
}