#include "capacitor_WIMA.h"

#include <stdio.h>
#include <cmath>
#include <float.h>

capacitor_WIMA::capacitor_WIMA(std::string name, float value, float usedU, float ratedU) : capacitor(name, value, usedU, ratedU){
	baseFIT = 10.;
}

capacitor_WIMA::~capacitor_WIMA(){

}

float capacitor_WIMA::getFIT(){

	float FIT = 1;
	float piT = 1;
	float temp = getDeviceTemperature() - component::KELVIN;	// use degree Centigrade for calculation

	if(temp <= 40.){
		piT = 1.;
	}else if(temp > 40 && temp <= 50){
		piT = 2.;
	}else if(temp > 50 && temp <= 70){
		piT = 5.;
	}else if(temp > 70 && temp <= 80){
		piT = 10.;
	}else if(temp > 80 && temp <= 100){
		piT = 15.;
	}else{
		fprintf(stderr, "Temperature %f to high for %s\n", temp, name.c_str()); 
		piT = FLT_MAX;
	}

	float stress = usedVoltage / ratedVoltage;
	float piU = 1.;

	if(stress <= 0.1){
		piU = 0.2;
	}else if(stress > 0.1 && stress <=0.25){
		piU = 0.3;
	}else if(stress > 0.25 && stress <=0.5){
		piU = 1;
	}else if(stress > 0.5 && stress <=0.75){
		piU = 2;
	}else if(stress > 0.75 && stress <=1.){
		piU = 5;
	}else{
		fprintf(stderr, "Voltage stress %f to high for %s\n", stress, name.c_str()); 
		piU = FLT_MAX;
	}

	FIT = baseFIT * piT * piU;

	return FIT;
}

