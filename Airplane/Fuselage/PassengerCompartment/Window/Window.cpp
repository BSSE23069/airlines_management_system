//
// Created by jammy on 06/04/2024.
//

#include "Window.h"

Window::Window(string ID, bool state)
    : windowID(ID), isCracked(state) {}

string Window::getWindowID() const{
  return windowID;
}

void Window ::setWindowCondition(bool value) {
  isCracked = value;
}

bool Window::isWindowCracked() const{
  return isCracked;
}