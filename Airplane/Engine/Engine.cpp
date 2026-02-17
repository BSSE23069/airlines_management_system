//
// Created by jammy on 06/04/2024.
//

#include "Engine.h"

Engine::Engine(string pos) {
  enginePosition = pos;
  isDamaged = false;
}

void Engine ::setEngineCondition( bool value ) {
  isDamaged = value;
}

string Engine::getEnginePosition() const {
  return enginePosition;
}

bool Engine::isEngineDamaged() const {
  return isDamaged;
}