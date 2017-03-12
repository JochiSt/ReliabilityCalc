#include "capacitor.h"

#include <cmath>
#include <float.h>

std::string capacitor::identifier = "C";
unsigned int capacitor::partcnt = 0;

capacitor::capacitor(std::string name, float value, float usedU, float ratedU) : component(name){
    capacity = value;
    usedVoltage = usedU;
    ratedVoltage = ratedU;

    stress = usedVoltage / ratedVoltage;

    partcnt++;
}

capacitor::capacitor(std::string name, float value, float stre) : component(name){
    capacity = value;

    usedVoltage = 0;
    ratedVoltage = 0;

    stress = stre;

    partcnt++;
}

capacitor::~capacitor(){
    //dtor
    partcnt--;
}

