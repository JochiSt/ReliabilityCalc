#include "IC.h"

#include <iostream>
#include <cmath>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

std::string IC::identifier = "U";
unsigned int IC::partcnt = 0;

IC::IC(std::string name, float fit_value, float fit_temperature_value) : component(name){
    FIT = fit_value;
    FIT_temperature = fit_temperature_value;

    if(FIT_temperature < KELVIN && FIT_temperature > 0){
        FIT_temperature += KELVIN;
    }
    partcnt++;
}

IC::~IC(){
    partcnt--;
}

float IC::getFIT(){
    float AF = exp(-1.*(EA/kB)*(1./(ambientTemperature)-1./(FIT_temperature)));    //aging factor
    return FIT * AF;
}

