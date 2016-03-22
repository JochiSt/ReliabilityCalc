#include "diode.h"

#include <iostream>
#include <cmath>

diode::diode(std::string name, float ratedU, float usedU, Application app, Dquality_t qual ) : component(name)
{
    usedVoltage = usedU;
    ratedVoltage = ratedU;
    applicationFactor = (float)app/10000.;
    qualityFactor = (float)qual;
}

diode::~diode()
{
    //dtor
}

float diode::getFIT(){
    switch(environment){
        case GB:
            environmentFactor = 1.0;
            break;
        case GF:
            environmentFactor = 6.0;
            break;
        case GM:
            environmentFactor = 9.0;
            break;
        case NS:
            environmentFactor = 9.0;
            break;
        case NU:
            environmentFactor = 19.0;
            break;
        case AIC:
            environmentFactor = 13.0;
            break;
        case AIF:
            environmentFactor = 29.0;
            break;
        case AUC:
            environmentFactor = 20.0;
            break;
        case AUF:
            environmentFactor = 43;
            break;
        case ARW:
            environmentFactor = 24;
            break;
        case SF:
            environmentFactor = 0.5;
            break;
        case MF:
            environmentFactor = 14;
            break;
        case ML:
            environmentFactor = 32;
            break;
        case CL:
            environmentFactor = 320;
            break;
    }

    double FIT;
    if(
       applicationFactor == 0.0038 || //general purpose analog
       applicationFactor == 0.0010 || //switching
       applicationFactor == 0.0690 || //power rectifier
       applicationFactor == 0.0030 || //Schottky Power Diode
       applicationFactor == 0.0013   //Transient Suppressor
    ){
        FIT = exp(-3091*(1./(ambientTemperature)-1./298.))*applicationFactor;
    }else if(
        applicationFactor == 0.0034 || //Current Regulator
        applicationFactor == 0.0020   //Voltage Regulator
    ){
        FIT = exp(-1925*(1./(ambientTemperature)-1./298.))*applicationFactor;
    }
    FIT *= qualityFactor;
    FIT *= environmentFactor;

    if(
        applicationFactor == 0.0013 ||  //Transient Suppressor
        applicationFactor == 0.0034 ||  //Current Regulator
        applicationFactor == 0.0020    //Voltage Regulator
    ){
        FIT *= 1.;                      //for completion
    }else{
        float stress = usedVoltage/ratedVoltage;
        FIT *= pow(stress,2.43);
    }

    std::cout << "\tCalculating FIT for " << name << "\tFIT: " << FIT << " / " << component::FITunit << std::endl;
    return FIT;     //This output was not tested!!!!
}
