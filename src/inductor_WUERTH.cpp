#include "inductor_WUERTH.h"

#include <cmath>
#include <float.h>

inductor_WUERTH::inductor_WUERTH(std::string name, std::string code) : inductor(name), component_WUERTH(code){

}

inductor_WUERTH::~inductor_WUERTH(){

}

float inductor_WUERTH::getFIT(){
	printf("%s using table %s, curve %c @ %f K\n", matchcode.c_str(), FIT_table.c_str(), FIT_curve, ambientTemperature);

	float FIT1, temp1;	// lower / equal temperature
	float FIT2, temp2;	// higher temperature
	component_WUERTH::getFIT(ambientTemperature, temp1, FIT1, temp2, FIT2);

	float FIT = FIT1 + (FIT2 - FIT1)/(temp2 - temp1) * (ambientTemperature - temp1);

	return FIT;
}

