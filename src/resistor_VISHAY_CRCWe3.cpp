#include "resistor_VISHAY_CRCWe3.h"
#include <float.h>

resistor_VISHAY_CRCWe3::resistor_VISHAY_CRCWe3(std::string name, float value, float usedP, float ratedP) : resistor(name, value, usedP, ratedP){

}
resistor_VISHAY_CRCWe3::resistor_VISHAY_CRCWe3(std::string name, float value, float stress) : resistor(name, value, stress){

}

float resistor_VISHAY_CRCWe3::getFIT(){
    if( stress < 1.){
        return 0.1;
    }else{
        /// return maximal possible value
        return FLT_MAX;
    }
}
