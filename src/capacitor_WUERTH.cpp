#include "capacitor_WUERTH.h"

#include <cmath>
#include <float.h>

capacitor_WUERTH::capacitor_WUERTH(std::string name, std::string code, float value, float usedU, float ratedU) : capacitor(name, value, usedU, ratedU), component_WUERTH(code){
    if(ratedVoltage > 50)   // do check, whether rated voltage is ok
        ratedVoltage = 50;
}

capacitor_WUERTH::~capacitor_WUERTH(){

}

float capacitor_WUERTH::getFIT(){
    return -1;
}

