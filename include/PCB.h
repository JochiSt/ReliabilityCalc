#ifndef PCB_H
#define PCB_H

#include "component.h"

#include <string>

/**
 * \brief calculation of the FIT value for a PCB
 *
 * The FIT value calculation is done using FIDES 2009 Edition A
 * http://www.fides-reliability.org/filed/UTE_Guide_FIDES_2009_Ed_A_EN.pdf
 * 
 * \author Jochen Steinmann
 * \date 2016-12-06
 * \version 0.2
 */
class PCB : public component {

	public:
		enum via_technology_t{
			THROUGH_HOLE = 25,
			BLIND_HOLE = 50,
			MICRO_VIA = 100,
			PADonVIA = 250	
		};

		/**
		 * constructor for the PCB
		 *
		 * \param[in] layers number of copperlayers in PCB-stack
		 * \param[in] connection number of solder connections to the PCB
		 * \param[in] tech technology of the vias
		 * \param[in] minTraceWidth minimal tracewidth AND minimal spacing in micrometer
		 */
		PCB(std::string name, int layers, int connection, via_technology_t tech, float minTraceWidth );
		virtual ~PCB();

		/// calculate the FIT value
		virtual float getFIT();		

		/// get PCB identifier
		static std::string getIdentifier(){
		    return identifier;
		}
		/// get the PCB count
		static unsigned int getPartCount(){
		    return partcnt;
		}

	protected:
		int layers;
		int connections;
		via_technology_t viatech;
		float minTraceWidth;

	private:
		static std::string identifier;	///< store capacitor identifier
		static unsigned int partcnt;	///< static variable for counting the parts
};

#endif
