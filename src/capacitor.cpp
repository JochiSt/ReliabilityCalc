#include "capacitor.h"

#include <cmath>
#include <float.h>

std::string capacitor::identifier = "C";
unsigned int capacitor::partcnt = 0;

capacitor::capacitor(std::string name, float value, float usedU, float ratedU) : component(name){
    capacity = value;
    usedVoltage = usedU;
    ratedVoltage = ratedU;
    partcnt++;
}

capacitor::~capacitor(){
    //dtor
    partcnt--;
}

