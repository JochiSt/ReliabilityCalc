#include "ESS.h"
#include <cmath>

float ESS::ScreenStrengthTC(float Trange, float dT, int cycles){
    float SSTC = 1. - exp( -0.0017 * pow(Trange + 0.6,0.6) * pow(log(exp(1)+dT),3) * cycles);
    return SSTC; 
}
