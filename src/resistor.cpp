#include "resistor.h"

#include <sstream>
#include <iostream>
#include <cmath>

std::string resistor::identifier = "R";

resistor::resistor(std::string name, float value, float usedP, float ratedP, Rquality_t qual, Rstyle_t styl) : component(name){
    resistance = value;
    usedPower = usedP;
    ratedPower = ratedP;
    qualityFactor = (float)qual / 100.;
    style = styl;
}

resistor::~resistor(){
    //dtor
}

float resistor::getFIT(){

    float stress = usedPower / ratedPower;

    if(calculation_method == MIL_HDBK_217F_NOTICE2){
        switch(environment){
            case GB:
                environmentFactor = 1.0;
                break;
            case GF:
                environmentFactor = 4.0;
                break;
            case GM:
                environmentFactor = 16;
                break;
            case NS:
                environmentFactor = 12;
                break;
            case NU:
                environmentFactor = 42;
                break;
            case AIC:
                environmentFactor = 18;
                break;
            case AIF:
                environmentFactor = 23;
                break;
            case AUC:
                environmentFactor = 31;
                break;
            case AUF:
                environmentFactor = 43;
                break;
            case ARW:
                environmentFactor = 63;
                break;
            case SF:
                environmentFactor = .50;
                break;
            case MF:
                environmentFactor = 37;
                break;
            case ML:
                environmentFactor = 87;
                break;
            case CL:
                environmentFactor = 1728;
                break;
        }

        float FIT = 0;
//######################################################
        // lambda_B
        if(style == RC || style == RCR){
            FIT = 0.0017;
        }else if(style == RZ || style == RTH ){
            FIT = 0.0019;
        }else if(style == RB || style == RBR ||
                 style == RW || style == RWR ||
                 style == RE || style == RER ||
                 style == RT || style == RTR ||
                 style == RR || style ==  RA ||
                 style == RK || style ==  RP ){
            FIT = 0.0024;
        }else{
            FIT = 0.0037;
        }
//######################################################
        // calculate pi_T
        if(style == RTH || style == RD) {
            // N/A
            FIT *= 1;
        }else{
            float EA = - 0.08;  // use column 2
            if(style == RC || style == RCR ||
                 style == RZ || style ==  RA ||
                 style == RK || style ==  RQ ||
                 style == RVC ){
                // use column 1
                EA = -0.2;
            }
            FIT *= exp( EA / 8.617E-5 * ( 1./ambientTemperature - 1./298.) );
        }
//######################################################
// calculate pi_S
        if(style == RZ || style == RTH){
            FIT *= 1;
        }else if(style == RC || style == RCR ||
                 style == RW || style == RWR ||
                 style == RE || style == RER ){
            // column 2
            FIT *= 0.54 * exp( 2.04 * stress);
        }else{
            // column 1
            FIT *= 0.71 * exp( 1.1 * stress );
        }
// calculate pi_P
        FIT *= pow(usedPower, 0.39);
//######################################################
// pi_Q
        FIT *= qualityFactor;
//######################################################
// pi_E
        FIT *= environmentFactor;

        return FIT;
    }else{
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
        float FIT = 0.000325 * exp(pow(ambientTemperature/343.,3)) * exp( stress*(ambientTemperature / 273.));
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

