#include "crystal_EPSON.h"

#include <cmath>
#include <float.h>
#include <stdio.h>

/**
 * constructor
 * @param name name of the component
 * @param basicFIT basic FIT value given by the manufacturer
 * @param basicFitTemp temperature of the given FIT value
 */
crystal_EPSON::crystal_EPSON(std::string name, float basicFIT, float basicFitTemp) : crystal(name, basicFIT, basicFitTemp){
    EA = 0.65;	// value given to Agnese from EPSON 2017-02-14
};

crystal_EPSON::~crystal_EPSON(){

};


