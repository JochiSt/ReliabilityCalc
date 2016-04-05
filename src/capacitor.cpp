#include "capacitor.h"

#include <sstream>
#include <iostream>
#include <cmath>

std::string capacitor::identifier = "C";
unsigned int capacitor::partcnt = 0;

capacitor::capacitor(std::string name, float value, float usedU, float ratedU, float ratedT, Cquality_t qual, Cstyle_t styl) : component(name){
    capacity = value;
    usedVoltage = usedU;
    ratedVoltage = ratedU;
    ratedTemperature = ratedT;
    quality = qual;
    style = styl;
    FIT_given = false;
    partcnt++;
}

capacitor::capacitor(std::string name, float fit_value, float fit_temperature_value, float fit_testvalue, float test_temperature_value, Unit_t fit_unit) : component(name){
    if((float)fit_unit<1000000.){       ///always if the UNIT is not MTTF
        FIT_ambient = fit_value/(float)fit_unit;
        FIT_test = fit_testvalue/(float)fit_unit;
    }else{
        FIT_ambient = (float)fit_unit/fit_value;
        FIT_test = (float)fit_unit/fit_testvalue;
    }
    FIT_temperature = fit_temperature_value+KELVIN;
    FIT_testTemperature = test_temperature_value+KELVIN;
    FIT_given = true;
    partcnt++;
}

capacitor::~capacitor(){
    //dtor
}

float capacitor::getFIT(){
    float FIT = 0;
    if(FIT_given){
        ///assume linear FIT change between two values
        return ((FIT_test-FIT_ambient)/(FIT_testTemperature-FIT_temperature)*(ambientTemperature-FIT_temperature) + FIT_ambient);
    }
    float stress = usedVoltage / ratedVoltage;
    if(calculation_method == MIL_HDBK_217F_NOTICE2){

//#################################################
// set lambda_B
        float lambda_B = 0;
        if(style == S_CP || style == S_CA ||
           style == S_CZ || style == S_CZR ||
           style == S_CH ){
            lambda_B = 0.00037;
        }else if(style == S_CQ || style == S_CQR ||
                 style == S_CHR || style == S_CFR ||
                 style == S_CRH){
                lambda_B = 0.00051;
        }else if(style == S_CM || style == S_CMR ||
                 style == S_CB || style == S_CY ||
                 style == S_CYR){
                lambda_B = 0.00076;
        }else if(style == S_CK || style == S_CKR ||
                 style == S_CC || style == S_CCR){
                lambda_B = 0.00099;
        }else if(style == S_CSR || style == S_CL ||
                 style == S_CLR || style == S_CRL){
                lambda_B = 0.00040;
        }else if(style == S_CDR){
            lambda_B = 0.0020;
        }else if(style == S_CWR){
            lambda_B = 0.00005;
        }else if(style == S_CU || style == S_CUR ||
                 style == S_CE){
                lambda_B = 0.00012;
        }else if(style == S_CV){
            lambda_B = 0.0079;
        }else if(style == S_PC || style == S_CG){
            lambda_B = 0.0060;
        }else if(style == S_CT){
            lambda_B = 0.0000072;
        }
//#################################################
// calculate pi_T
        float EA = -0.15;    // use column 1
        if(style == S_CMR || style == S_CM ||
           style ==  S_CB || style == S_CY ||
           style == S_CYR || style == S_CK ||
           style == S_CKR || style == S_CC ||
           style == S_CCR || style == S_CU ||
           style == S_CUR || style == S_CE ||
           style ==  S_PC || style == S_CT ){
            EA = -0.35;      // use column 2
        }
        float pi_T = 0;
        if((ambientTemperature < ratedTemperature+KELVIN) && (ratedTemperature < 150.) ){
            pi_T = exp( EA / kB * ( 1./ambientTemperature - 1./(25. + KELVIN) ) );
        }else if(ambientTemperature < ratedTemperature+KELVIN){
            // use equation for applications above 150 degC
            pi_T = 0;
        }
//#################################################
// calculate pi_C
        float pi_C = pow(capacity / 1E6, 0.09); // use column 1
        if(style == S_CSR || style == S_CWR ||
           style == S_CL  || style == S_CLR ||
           style == S_CU  || style == S_CUR ||
           style == S_CE ){
            pi_C = pow(capacity / 1E6, 0.23);
        }
//#################################################
// calculate pi_V
        float pi_V = 0;
        float expo = 0;
        float div = 0.6;
// column1
        if(style == S_CP || style == S_CA ||
           style == S_CZ || style == S_CZR ||
           style == S_CQ || style == S_CQR ||
           style == S_CH || style == S_CHR ||
           style == S_CFR || style == S_CRH ||
           style == S_CU || style == S_CUR ||
           style == S_CE){
            expo = 5;
// column2
        }else if(style == S_CM || style == S_CMR ||
                 style == S_CB || style == S_CY ||
                 style == S_CYR ){
            expo = 10;
// column3
        }else if(style == S_CK || style == S_CKR ||
                 style == S_CC || style == S_CCR ||
                 style == S_CDR){
            expo = 3;
// column4
        }else if(style == S_CSR || style == S_CWR ||
                 style == S_CL || style == S_CLR ||
                 style == S_CRL){
            expo = 17;
// column5
        }else if(style == S_CV || style == S_PC ||
                 style == S_CT || style == S_CG){
            expo = 3;
            div = 0.5;
        }
        pi_V = pow( stress / div, expo) + 1;
//#################################################
// calculate pi_SR
        float pi_SR = 1;
        if(style == S_CSR || style == S_CWR){
            // see pi_SR table
            pi_SR = 0;  //FIXME to be implemented
        }
//#################################################
// calculate pi_Q
        float pi_Q = (float)quality / 1000.;
        if(quality == Q_L){
            pi_Q = 1.5;
        }
//#################################################
// calculate pi_E
        float pi_E = 0;
        switch(environment){
            case GB:
                pi_E = 1.0;
                break;
            case GF:
                pi_E = 10;
                break;
            case GM:
                pi_E = 20;
                break;
            case NS:
                pi_E = 7.0;
                break;
            case NU:
                pi_E = 15;
                break;
            case AIC:
                pi_E = 12;
                break;
            case AIF:
                pi_E = 15;
                break;
            case AUC:
                pi_E = 25;
                break;
            case AUF:
                pi_E = 30;
                break;
            case ARW:
                pi_E = 40;
                break;
            case SF:
                pi_E = .50;
                break;
            case MF:
                pi_E = 20;
                break;
            case ML:
                pi_E = 50;
                break;
            case CL:
                pi_E = 570;
                break;
        }
//#################################################
// calculate FIT
        FIT = lambda_B * pi_T * pi_C * pi_V * pi_SR * pi_Q * pi_E;
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
        float FIT = 0.0003 * ( pow(stress/0.3, 3) + 1) * exp( ambientTemperature / (ratedTemperature + KELVIN));
        FIT *= 0.41 * pow(capacity, 0.11);
        FIT *= (float)quality / 1000.;
        FIT *= environmentFactor;
 //       std::cout << "\tCalculating FIT for " << name << "\tFIT: " << FIT << " / " << component::FITunit << std::endl;
        return FIT;
    }
}

std::string capacitor::toString(){
    std::ostringstream os;
    os << identifier << "\t";
    os << name << "\t";
    os << capacity << "\t";
    os << usedVoltage << "\t";
    os << ratedVoltage << "\t";
    os << ratedTemperature << "\t";
    os << qualityFactor;
    return os.str();
}

int capacitor::fromString(std::string value){
    std::istringstream is;
    is.str(value);
    std::string ident;
    is >> ident;

    if(ident == identifier ){
        is >> name >> capacity >> usedVoltage >> ratedVoltage >> ratedTemperature >> qualityFactor;
        return 0;
    }else{
        return -1;
    }
}
