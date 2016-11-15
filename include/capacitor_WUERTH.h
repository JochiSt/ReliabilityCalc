#ifndef CAPACITOR_WUERTH_H
#define CAPACITOR_WUERTH_H

#include "capacitor.h"

/**
 * @brief Implementation of reliability for Wuerth capacitors
 * data based on LINK EINFÜGEN
 */ 

class capacitor_WUERTH : public capacitor{

	public:
		/// constructor for Würth capacitors
        	virtual capacitor_wuerth(std::string name, float value, float usedU, float ratedU);

		/// @return FIT of this specific component
		virtual float getFIT();

	private:

};

#endif
