#include "capacitor_WUERTH.h"

#include <cmath>
#include <float.h>

capacitor_WUERTH::capacitor_WUERTH(std::string name, std::string code, float value, float usedU, float ratedU) : capacitor(name, value, usedU, ratedU), component_WUERTH(code){
    if(ratedVoltage > 50)   // do check, whether rated voltage is ok
        ratedVoltage = 50;
}

capacitor_WUERTH::~capacitor_WUERTH(){

}

float capacitor_WUERTH::getFIT(){
	float stress = usedVoltage / ratedVoltage;
	char curve = FIT_curve;

	if( curve == '-' ){
		printf("no curve found for %s\n", name.c_str());
		return FLT_MAX;
	}

	if(stress <= 0.3){ // use the basic curve
	}else if(stress > 0.3 && stress <= 0.5){
		curve += 1;
	}else if(stress > 0.5 && stress <= 0.7){
		curve += 2;
	}else if(stress > 0.7 && stress <= 1.){
		curve += 3;
	}else if(stress > 1.){
		return FLT_MAX;
	}

//	printf("%s using table %s, curve %c @ %f K - %f\n", matchcode.c_str(), FIT_table.c_str(), curve, ambientTemperature, usedVoltage/ratedVoltage);

	float FIT1, temp1;	// lower / equal temperature
	float FIT2, temp2;	// higher temperature

	component_WUERTH::getFIT(ambientTemperature, temp1, FIT1, temp2, FIT2, curve);

	float FIT = FIT1 + (FIT2 - FIT1)/(temp2 - temp1) * (ambientTemperature - temp1);

	return FIT;
}

