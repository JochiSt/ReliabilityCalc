#include "component.h"

float component::ambientTemperature = 298.15;                       // init to 25°C
component::environment_t component::environment = component::GB;    // init with easiest environment
std::string component::FITunit = "1E6 h";

component::component(std::string val){
    name = val;
}

/**
    switch(env){
        case GB:
            break;
        case GF:
            break;
        case GM:
            break;
        case NS:
            break;
        case NU:
            break;
        case AIC:
            break;
        case AIF:
            break;
        case AUC:
            break;
        case AUF:
            break;
        case ARW:
            break;
        case SF:
            break;
        case MF:
            break;
        case ML:
            break;
        case CL:
            break;
    }
*/

component::~component(){
    //dtor
}
