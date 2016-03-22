#include "resistor.h"

#include <sstream>
#include <iostream>
#include <cmath>

std::string resistor::identifier = "R";

resistor::resistor(std::string name, float value, float usedP, float ratedP, Rquality_t qual) : component(name){
    resistance = value;
    usedPower = usedP;
    ratedPower = ratedP;
    qualityFactor = (float)qual / 100.;
}

resistor::~resistor(){
    //dtor
}

float resistor::getFIT(){
    switch(environment){
        case GB:
            environmentFactor = 1.0;
            break;
        case GF:
            environmentFactor = 2.0;
            break;
        case GM:
            environmentFactor = 8.0;
            break;
        case NS:
            environmentFactor = 4.0;
            break;
        case NU:
            environmentFactor = 14.0;
            break;
        case AIC:
            environmentFactor = 4.0;
            break;
        case AIF:
            environmentFactor = 8.0;
            break;
        case AUC:
            environmentFactor = 10.0;
            break;
        case AUF:
            environmentFactor = 18;
            break;
        case ARW:
            environmentFactor = 19;
            break;
        case SF:
            environmentFactor = 0.2;
            break;
        case MF:
            environmentFactor = 10;
            break;
        case ML:
            environmentFactor = 28;
            break;
        case CL:
            environmentFactor = 510;
            break;
    }

    float stress = usedPower / ratedPower;
    double FIT = 0.000325 * exp(pow(ambientTemperature/343.,3)) * exp( stress*(ambientTemperature / 273.));
    if(resistance< 0.1){
        FIT *= 1.;
    }else if(resistance < 1.){
        FIT *= 1.1;
    }else if(resistance < 10.){
        FIT *= 1.6;
    }else{
        FIT *= 2.5;
    }
    FIT *= qualityFactor;
    FIT *= environmentFactor;
    std::cout << "\tCalculating FIT for " << name << "\tFIT: " << FIT << " / " << component::FITunit << std::endl;
    return FIT;
}

std::string resistor::toString(){
    std::ostringstream os;
    os << identifier << "\t";
    os << name << "\t";
    os << resistance << "\t";
    os << usedPower << "\t";
    os << ratedPower << "\t";
    os << qualityFactor;
    return os.str();
}

int resistor::fromString(std::string value){
    std::istringstream is;
    is.str(value);
    std::string ident;
    is >> ident;
    if(ident == identifier){
        is >> name >> resistance >> usedPower >> ratedPower >> qualityFactor;
        return 0;
    }else{
        return -1;
    }
}

