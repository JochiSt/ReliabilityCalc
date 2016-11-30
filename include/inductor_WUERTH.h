#ifndef INDUCTOR_WUERTH_H
#define INDUCTOR_WUERTH_H

#include "inductor.h"
#include "component_WUERTH.h"
/**
 * @brief Implementation of reliability for Wuerth inductors
 * data based on LINK EINFÜGEN
 */
class inductor_WUERTH : public inductor, public component_WUERTH {

	public:
		/// constructor for Würth capacitors
		inductor_WUERTH(std::string name, std::string code);
		virtual ~inductor_WUERTH();

		/// @return FIT of this specific component
		virtual float getFIT();

	private:

};

#endif
