#include "capacitor_WIMA_SMD_PPS.h"

#include <cmath>
#include <float.h>

capacitor_WIMA_SMD_PPS::capacitor_WIMA_SMD_PPS(std::string name, float value, float usedU, float ratedU) : capacitor_WIMA(name, value, usedU, ratedU){
	baseFIT = 2.;
}

capacitor_WIMA_SMD_PPS::~capacitor_WIMA_SMD_PPS(){

}

