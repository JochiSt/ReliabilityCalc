#include "inductor_MIL_HDBK_217F.h"

#include <iostream>
#include <cmath>
#include <sstream>

inductor_MIL_HDBK_217F::inductor_MIL_HDBK_217F(std::string name, float ratedT, Iquality_t qual) : inductor(name), component_MIL_HDBK_217F(name) {
    ratedTemperature = ratedT;
    qualityFactor = (float)qual / 100.;
    FIT = 0;
}

inductor_MIL_HDBK_217F::~inductor_MIL_HDBK_217F(){

}

float inductor_MIL_HDBK_217F::getFIT(){
    if(FIT!=0){
//        std::cout << "\tCalculating FIT for " << name << "\tFIT: " << FIT << " / " << component::FITunit << std::endl;
        return FIT;
    }
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

    FIT = 0;
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
//    std::cout << "\tCalculating FIT for " << name << "\tFIT: " << FIT << " / " << component::FITunit << std::endl;
    return FIT;
}

