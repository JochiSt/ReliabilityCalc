#include "IC.h"

#include <iostream>
#include <cmath>
#include <sstream>

std::string IC::identifier = "U";

IC::IC(std::string name, float fit_value, float fit_temperature_value, Unit_t fit_unit) : component(name){
    if((float)fit_unit<1000000.){       ///always if the UNIT is not MTTF
        FIT = fit_value/(float)fit_unit;
    }else{
        FIT = (float)fit_unit/fit_value;
    }

    FIT_temperature = fit_temperature_value;
}

float IC::getFIT(){
    float AF = exp(EA/kB*(1/(ambientTemperature)-1/(FIT_temperature+273)));    //aging factor
    FIT *= AF;
//    std::cout << "\tCalculating FIT for " << name << "\tFIT: " << FIT << " / " << component::FITunit << std::endl;
    return FIT;
}

std::string IC::toString(){
    std::ostringstream os;
    os << identifier << "\t";
    os << name << "\t";
    os << FIT << "\t";
    os << FIT_temperature;
    return os.str();
}

int IC::fromString(std::string value){
    std::istringstream is;
    is.str(value);
    std::string ident;
    is >> ident;
    if(ident == identifier){
        is >> name >> FIT >> FIT_temperature;
        return 0;
    }else{
        return -1;
    }
}
