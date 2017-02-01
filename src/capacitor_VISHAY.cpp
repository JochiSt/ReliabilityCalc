#include "capacitor_VISHAY.h"

#include <stdio.h>
#include <cmath>
#include <float.h>

capacitor_VISHAY::capacitor_VISHAY(std::string name, capacitor_class_t cClass, float value, float usedU, float ratedU) : capacitor(name, value, usedU, ratedU){
	cap_class = cClass;
}

capacitor_VISHAY::~capacitor_VISHAY(){

}

float capacitor_VISHAY::getFIT(){
	float FIT = FLT_MAX;
//	float temp = getDeviceTemperature() - component::KELVIN;	// use degree Centigrade for calculation

	if(cap_class == CLASS_1){
		FIT = 2;
	}
	else if(cap_class == CLASS_2){
		FIT = 5;
	}

	float stress = usedVoltage / ratedVoltage;
	if(stress > 0.5){
		fprintf(stderr, "Voltage stress %f to high for %s\n", stress, name.c_str()); 
		FIT = FLT_MAX;
	}

	return FIT;
}

