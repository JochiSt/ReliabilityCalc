#include "crystal.h"

#include <cmath>
#include <float.h>
#include <stdio.h>

std::string crystal::identifier = "Q";
unsigned int crystal::partcnt = 0;

/**
 * constructor
 * @param name name of the component
 * @param basicFIT basic FIT value given by the manufacturer
 * @param basicFitTemp temperature of the given FIT value
 */
crystal::crystal(std::string name, float basicFIT, float basicFitTemp) : component(name){
    BaseFit = basicFIT;
    FITtemp = basicFitTemp; 

    if(basicFitTemp < component::KELVIN){
	FITtemp += component::KELVIN;
    }

    EA = 0.6;
};

crystal::~crystal(){

};

float crystal::getFIT(){
    printf("using EA = %f\n", EA);
    float useTemperature = getDeviceTemperature();
    float AF = exp(-1.*(EA/kB)*(1./(useTemperature)-1./(FITtemp)));    //aging factor
    return BaseFit * AF;
};


