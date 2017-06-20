#include "resistor_SRT.h"
#include <float.h>

resistor_SRT::resistor_SRT(std::string name, float value, float usedP, float ratedP) : resistor(name, value, usedP, ratedP){

}
resistor_SRT::resistor_SRT(std::string name, float value, float stress) : resistor(name, value, stress){

}

float resistor_SRT::getFIT(){
    if( stress < 1.){
        return 0.5;
    }else{
        /// return maximal possible value
        return FLT_MAX;
    }
}
