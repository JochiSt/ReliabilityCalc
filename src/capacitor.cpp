#include "capacitor.h"

#include <iostream>
#include <cmath>

capacitor::capacitor(std::string name, float value, float usedU, float ratedU, float ratedT, Cquality_t qual) : component(name){
    capacity = value;
    usedVoltage = usedU;
    ratedVoltage = ratedU;
    ratedTemperature = ratedT;
    qualityFactor = (float)qual / 100.;
}

capacitor::~capacitor(){
    //dtor
}

float capacitor::getFIT(){
    switch(environment){
        case GB:
            environmentFactor = 1.0;
            break;
        case GF:
            environmentFactor = 2.0;
            break;
        case GM:
            environmentFactor = 9.0;
            break;
        case NS:
            environmentFactor = 5.0;
            break;
        case NU:
            environmentFactor = 15.0;
            break;
        case AIC:
            environmentFactor = 4.0;
            break;
        case AIF:
            environmentFactor = 4.0;
            break;
        case AUC:
            environmentFactor = 8.0;
            break;
        case AUF:
            environmentFactor = 12;
            break;
        case ARW:
            environmentFactor = 20;
            break;
        case SF:
            environmentFactor = 0.4;
            break;
        case MF:
            environmentFactor = 13;
            break;
        case ML:
            environmentFactor = 34;
            break;
        case CL:
            environmentFactor = 610;
            break;
    }

    std::cout << "\tCalculating FIT for " << name << std::endl;
    float stress = usedVoltage / ratedVoltage;
    double FIT = 0.0003 * ( pow(stress, 3) + 1) * exp( ambientTemperature / ratedTemperature);
    FIT *= 0.41 * pow(capacity, 0.11);
    FIT *= qualityFactor;
    FIT *= environmentFactor;
    return 2;
}
