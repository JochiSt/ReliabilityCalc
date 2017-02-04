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
 * \author Jochen Steinmann, Florian Lenz
 * \date 2016-12-06
 * \version 0.2
 */
class PCB : public component {

	public:
		/**
		 * 
		 *
		 */
		enum via_technology_t{
			THROUGH_HOLE = 25,  ///< normal through hole vias
			BLIND_HOLE = 50,    ///< Blind Vias
			MICRO_VIA = 100,    ///< Micro Vias
			PADonVIA = 250	    ///< Pad on Via
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
		int layers;			///< Number of layers of the PCB stack
		int connections;		///< number of connections
		via_technology_t viatech;	///< via technology
		float minTraceWidth;		///< minimal trace width and minimal distance between two traces
		float enviroment;		///< operation environment

		int n_annual; 			///< Cycles per Year on - off - on
						///< default = 2 (assumed JUNO gets shut down 2 times per year)
		float t_annual;			///< Duration of the shutdowns 
						///< default = 10 (2x5hours)
		float delta_T;			///< Temperature difference between electronics ON and OFF
						///< default = 20;

		float pi_sal; 			///< \brief saline pollution level
						///< high = 2, low(default) = 1
		float pi_prot;	 		///< \brief product protection level
						///< hermetic = 0, non hermetic(default) =1
		float pi_zone;			///< \brief application pollution level
						///< Low(default) = 1, Moderate = 2, High =4
		float pi_evir;			///< \brief enviromental pollution level
						///< Low(default) = 1, Moderate = 1.5, High = 4
		float G_RMS;			///< \brief stres associated with each random vibration phase
						///< for further information please look into FIDES, default = 0
		float RH;			///< \brief humidity in %
						///< default = 10 %
		float pi_process;		///< \brief default = 4. 
						///< Every manufacturer etc. has to be marked <- not possible for JUNO
		float pi_placement;		///< \brief default for PCB = 1
		float pi_application;		///< \brief default for JUNO = 1.8
		float pi_ruggedising;		///< \brief default = 1.7
		float C_sensibility;		///< \brief default for PCB = 6.5

		/**
 		 * \brief Quality Assurance
		 *
		 * ISO/TS 16949 V2002, e.g. VISHAY = 3
		 * QS9000, TL9000,ISO/TS 29001, EN9100, AS9100, JISQ 9100, AQAP 2110, AQAP 2120, AQAP 2130, IRIS,
		 * IEC TS 62239, ESA/ECSS QPL, MIL-PRF-38535 QML, MIL-PRF-19500 = 2
		 * ISO 9000 version 2000 certified, e.g. ESW = 1 (default)
		 * No Information = 0
		 */
		float QA_manufacturer;		

		/**
		 * \brief Component quality assurence level
		 *
 		 * Component quality assurence level: Position relative to the state of the art:
 		 * Higher = 3
 		 * Equivalent = 2 (default)
 		 * Lower = 1
 		 * Very much lower = 0
 		 */
		float QA_component;
	
		/**
		 * \brief Risk related to the use of this manufacturer	
		 *
		 * risk related to the use of this manufacturer
		 * Recognised manufacturer: Mature process for the item considered = 4
		 * Recognised manufacturer: Process not analysed or not mature for the item considered = 3
		 * Manufacturer not recognised (for example never audited) or small series production = 2 (default)
		 * Previous disqualification or problem with feedback from operations = 1
		 */
		float E_risk;

	private:
		static std::string identifier;	///< store capacitor identifier
		static unsigned int partcnt;	///< static variable for counting the parts
};

#endif
