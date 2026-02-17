//
// Created by jammy on 06/04/2024.
//

#include "LandingGear.h"

LandingGear::LandingGear(int tyresCount, int strutsCount)
    : totalTyres(tyresCount), totalStruts(strutsCount) {
  setLandingGear();
}

void LandingGear::setLandingGear() {

  // Orientation of tyres in a landing gear

  for (int i = 0, n = 1, m = 1; i < totalTyres || i < totalStruts; ++i) {
    if( i % 2 == 0 ) {
      tyres.emplace_back("LT" + to_string(n), 0);
      struts.emplace_back("LS" + to_string(n), 0);
      n += 1;
    }
    else {
      tyres.emplace_back("RT" + to_string(m), 0);
      struts.emplace_back("RS" + to_string(n), 0);
      m += 1;
    }
  }
}

vector<Tyre> &LandingGear::getTyres()  {
  return tyres;
}

vector<Strut> &LandingGear::getStruts()  {
  return struts;
}