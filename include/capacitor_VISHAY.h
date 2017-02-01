#ifndef CAPACITOR_VISHAY_H
#define CAPACITOR_VISHAY_H

#include "capacitor.h"

/**
 * @brief Implementation of reliability for VISHAY capacitors
 * implementation according to VISHAY Document Number 22001
 * 	http://www.vishay.com/docs/22001/geninfocdiscrfisafe.pdf
 *	from Feb 1st 2017
 */
class capacitor_VISHAY : public capacitor {

	public:
		enum capacitor_class_t {
			CLASS_1 = 1,
			CLASS_2 = 2
		};

		/// constructor for general VISHAY capacitors
        	capacitor_VISHAY(std::string name, capacitor_class_t cClass, float value, float usedU, float ratedU);
	        virtual ~capacitor_VISHAY();

		/// @return FIT of this specific component
		virtual float getFIT();

	protected:
		capacitor_class_t cap_class;

	private:

};

#endif
