#include "IC.h"

#include <iostream>
#include <cmath>

IC::IC(std::string name, float fit_value, float fit_temperature_value, Unit_t fit_unit) : component(name){
    if((float)fit_unit<1000000.){       //always if the UNIT is not MTTF
        FIT = fit_value*(float)fit_unit;
    }else{
        FIT = (float)fit_unit/fit_value;
    }

    FIT_temperature = fit_temperature_value;
}

IC::~IC()
{
    //dtor
}

float IC::getFIT(){
    float AF = exp(EA/kB*(1/(ambientTemperature)-1/(FIT_temperature+273)));    //aging factor
    FIT *= AF;
    std::cout << "\tCalculating FIT for " << name << "\tFIT: " << FIT << " / " << component::FITunit << std::endl;
    return FIT;
}
