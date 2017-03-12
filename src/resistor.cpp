#include "resistor.h"

#include <sstream>
#include <iostream>
#include <cmath>
#include <float.h>

std::string resistor::identifier = "R";
unsigned int resistor::partcnt = 0;

resistor::resistor(std::string name, float value, float usedP, float ratedP) : component(name){
    resistance = value;
    usedPower = usedP;
    ratedPower = ratedP;

    stress = usedPower / ratedPower;

    partcnt++;
}

resistor::resistor(std::string name, float value, float stre) : component(name){
    resistance = value;
    usedPower = 0;
    ratedPower = 0;

    stress = stre;

    partcnt++;
}

