#include "diode.h"

#include <sstream>
#include <iostream>
#include <cmath>

std::string diode::identifier = "D";

diode::diode(std::string name, float usedU, float ratedU, application_t app, quality_t qual ) : component(name)
{
    usedVoltage = usedU;
    ratedVoltage = ratedU;
    application = app;
    applicationFactor = (float)app/10000.;
    qualityFactor = (float)qual/100.;
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

    //float applicationFactor = (float)application/10000.;

    double FIT = 0;
    if(
       application == GENERAL_PURPOSE_ANALOG || // general purpose analog
       application == SWITCHING ||              // switching
       application == POWER_RECTIFIER ||        // power rectifier
       application == SCHOTTKY ||               // Schottky Power Diode
       application == TRANSIENT_SUPPRESSOR ||   // Transient Suppressor
       application == PR_HIGH_VOLTAGE
    ){
        FIT = exp(-3091*(1./(ambientTemperature)-1./298.))*applicationFactor;
    }else if(
        application == CURRENT_REGULATOR ||     // Current Regulator
        application == VOLTAGE_REGULATOR        // Voltage Regulator
    ){
        FIT = exp(-1925*(1./(ambientTemperature)-1./298.))*applicationFactor;
    }

    FIT *= qualityFactor;
    FIT *= environmentFactor;

    if(
        application == TRANSIENT_SUPPRESSOR ||  // Transient Suppressor
        application == CURRENT_REGULATOR    ||  // Current Regulator
        application == VOLTAGE_REGULATOR        // Voltage Regulator
    ){
        FIT *= 1.;                      //for completion
    }else{
        float stress = usedVoltage/ratedVoltage;
        FIT *= pow(stress,2.43);
    }

    std::cout << "\tCalculating FIT for " << name << "\tFIT: " << FIT << " / " << component::FITunit << std::endl;
    return FIT;     //This output was not tested!!!!
}

std::string diode::toString(){
    std::ostringstream os;
    os << identifier << "\t";
    os << name << "\t";
    os << usedVoltage << "\t";
    os << ratedVoltage << "\t";
    os << applicationFactor << "\t";
    os << qualityFactor;
    return os.str();
}

int diode::fromString(std::string value){
    std::istringstream is;
    is.str(value);
    std::string ident;
    is >> ident;
    if(ident == identifier){
        is >> name >> usedVoltage >> ratedVoltage >> applicationFactor >> qualityFactor;
        return 0;
    }else{
        return -1;
    }
}
