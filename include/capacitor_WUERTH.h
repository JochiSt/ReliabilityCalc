#ifndef CAPACITOR_WUERTH_H
#define CAPACITOR_WUERTH_H

#include "capacitor.h"
#include "component_WUERTH.h"
/**
 * @brief Implementation of reliability for Wuerth capacitors
 * data based on LINK EINFÜGEN
 */
class capacitor_WUERTH : public capacitor, public component_WUERTH {

	public:
		/// constructor for Würth capacitors
        capacitor_WUERTH(std::string name, std::string code, float value, float usedU, float ratedU);
        virtual ~capacitor_WUERTH();

		/// @return FIT of this specific component
		virtual float getFIT();

	private:

};

#endif
