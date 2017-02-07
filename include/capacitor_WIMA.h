#ifndef CAPACITOR_WIMA_H
#define CAPACITOR_WIMA_H

#include "capacitor.h"

/**
 * @brief Implementation of reliability for WIMA capacitors
 * @author Jochen Steinmann
 * @date 2017-02-03
 *
 * details can be found at http://www.wima.com/EN/reliability.htm
 */
class capacitor_WIMA : public capacitor {

	public:
		/// constructor for general WIMA capacitors
        	capacitor_WIMA(std::string name, float value, float usedU, float ratedU);
	        virtual ~capacitor_WIMA();

		/// @return FIT of this specific component
		virtual float getFIT();

	protected:
		float baseFIT;

	private:

};

#endif
