#include "inductor.h"

#include <iostream>
#include <cmath>
#include <sstream>

std::string inductor::identifier = "L";

inductor::inductor(std::string name, float ratedT, Iquality_t qual) : component(name)
{
    ratedTemperature = ratedT;
    qualityFactor = (float)qual / 100.;
}

float inductor::getFIT(){
    switch(environment){
        case GB:
            environmentFactor = 1.0;
            break;
        case GF:
            environmentFactor = 4.0;
            break;
        case GM:
            environmentFactor = 12.0;
            break;
        case NS:
            environmentFactor = 5.0;
            break;
        case NU:
            environmentFactor = 16.0;
            break;
        case AIC:
            environmentFactor = 5.0;
            break;
        case AIF:
            environmentFactor = 7.0;
            break;
        case AUC:
            environmentFactor = 6.0;
            break;
        case AUF:
            environmentFactor = 8;
            break;
        case ARW:
            environmentFactor = 24;
            break;
        case SF:
            environmentFactor = 0.5;
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

    double FIT;
    if(ratedTemperature>125){
        FIT = 0.000335*exp(pow((ambientTemperature)/329.,15.6));
    }else if(ratedTemperature>105){
        FIT = 0.000379*exp(pow((ambientTemperature)/352.,14));
    }else if(ratedTemperature>85){
        FIT = 0.000319*exp(pow((ambientTemperature)/364.,6.7));
    }else{
        FIT = 0.00035*exp(pow((ambientTemperature)/409.,10));
    }
    FIT *= qualityFactor;
    FIT *= environmentFactor;
    std::cout << "\tCalculating FIT for " << name << "\tFIT: " << FIT << " / " << component::FITunit << std::endl;
    return FIT;
}

std::string inductor::toString(){
    std::ostringstream os;
    os << identifier << "\t";
    os << name << "\t";
    os << ratedTemperature << "\t";
    os << qualityFactor;
    return os.str();
}

int inductor::fromString(std::string value){
    std::istringstream is;
    is.str(value);
    std::string ident;
    is >> ident;
    if(ident == identifier){
        is >> name >> ratedTemperature >> qualityFactor;
        return 0;
    }else{
        return -1;
    }
}

