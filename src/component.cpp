#include "component.h"

float component::ambientTemperature = 323;                           // init to 40�C
component::environment_t component::environment = component::GB;        // init with easiest environment
std::string component::FITunit = "1E6 h";                               // set fit unit to MIL HDBK
component::calc_method_t component::calculation_method = MIL_HDBK_217F; // for normal use MIL HDBK without notice

component::component(std::string val){
    name = val;
}

/*
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
