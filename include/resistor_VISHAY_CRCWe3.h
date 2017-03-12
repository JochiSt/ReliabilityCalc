/*
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  FIT calculation useful for VISHAY CRCWe3 resistors
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef RESISTOR_VISHAY_CRCRE3_H
#define RESISTOR_VISHAY_CRCRE3_H

#include "resistor.h"

class resistor_VISHAY_CRCWe3 : public resistor {
	public:
        	resistor_VISHAY_CRCWe3(std::string name, float value, float usedPower, float ratedPower);
        	resistor_VISHAY_CRCWe3(std::string name, float value, float stress);
		virtual float getFIT();
};

#endif
