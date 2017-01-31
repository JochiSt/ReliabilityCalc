#ifndef CAPACITOR_WIMA_SMD_PPS_H
#define CAPACITOR_WIMA_SMD_PPS_H

#include "capacitor_WIMA.h"

/**
 * @brief Implementation of reliability for WIMA SMD PPS capacitors
 */
class capacitor_WIMA_SMD_PPS : public capacitor_WIMA {

	public:
		/// constructor for Würth capacitors
        	capacitor_WIMA_SMD_PPS(std::string name, float value, float usedU, float ratedU);
	        virtual ~capacitor_WIMA_SMD_PPS();
};

#endif
