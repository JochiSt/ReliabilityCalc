/*
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  FIT calculation useful for SRT russian resistors
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef RESISTOR_SRT_H
#define RESISTOR_SRT_H

#include "resistor.h"

class resistor_SRT : public resistor {
	public:
        	resistor_SRT(std::string name, float value, float usedPower, float ratedPower);
        	resistor_SRT(std::string name, float value, float stress);
		virtual float getFIT();
};

#endif
