#include "PCB.h"
#include <float.h>
#include <cmath>

std::string PCB::identifier = "PCB";
unsigned int PCB::partcnt = 0;

PCB::PCB(std::string name, int lay, int conn, via_technology_t tech, float minTraceW ) : component(name){
	layers = lay;
	connections = conn;
	viatech = tech;
	minTraceWidth = minTraceW;
	partcnt++;

	// Things needed for FIDES
	n_annual = 2; 	// Cycles per Year (assumed JUNO gets shut down 2 times per year)
	t_annual = 10;	// Duration of the shutdowns (2x5hours)
	delta_T = 20;	// Temperature difference between electronics ON and OFF

	pi_sal = 1; 	// saline pollution level. high = 2, low = 1
	pi_prot = 1; 	// product protection level. hermetic = 0, non hermetic =1
	pi_zone = 1;	// application pollution level. Low = 1, Moderate = 2, High =4
	pi_evir = 1;	// enviromental pollution level. Low = 1, Moderate = 1.5, High = 4
	G_RMS = 0;	// stres associated wiht each random vibration phase, for further information please look into FIDES
	RH = 10;	// humidity in %
	
	pi_process = 4;		// default. Every manufacturer etc. has to be marked <- not possible for JUNO
	pi_placement = 1;	// default for PCB
	pi_application = 1.8;	// default for JUNO
	pi_ruggedising = 1.7;	// default
	C_sensibility = 6.5;	// default for PCB
	QA_manufacturer = 1;	// Quality Assurance: 
				// ISO/TS 16949 V2002, e.g. vishay = 3
				// QS9000, TL9000,ISO/TS 29001, EN9100, AS9100, JISQ 9100, AQAP 2110, AQAP 2120, AQAP 2130, IRIS, IEC TS 62239, ESA/ECSS QPL, MIL-PRF-38535 QML, MIL-PRF-19500 = 2
				// ISO 9000 version 2000 certified, e.g. ESW = 1
				// No Information = 0
	QA_component = 2;	// Component quality assurence level: Position relative to the state of the art:
				// Higher = 3
				// Equivalent = 2
				// Lower = 1
				// Very much lower = 0
	E_risk = 3;		// risk related to the use of this manufacturer
				// Recognised manufacturer: Mature process for the item considered = 4
				// Recognised manufacturer: Process not analysed or not mature for the item considered = 3
				// Manufacturer not recognised (for example never audited) or small series production = 2
				// Previous disqualification or problem with feedback from operations = 1
	
	
}


PCB::~PCB(){
	partcnt--;
}

float PCB::getFIT(){
	float PCB_class = 1.;
	if( minTraceWidth < 500 && minTraceWidth >= 310 ){
		PCB_class = 2.;
	}else if( minTraceWidth < 310 && minTraceWidth >= 210 ){
		PCB_class = 3.;
	}else if( minTraceWidth < 210 && minTraceWidth >= 150 ){
		PCB_class = 4.;
	}else if( minTraceWidth < 150 && minTraceWidth >= 125 ){
		PCB_class = 5.;
	}else if( minTraceWidth < 125 && minTraceWidth >= 100 ){
		PCB_class = 6.;
	}else if( minTraceWidth < 100 ){
		PCB_class = FLT_MAX;
	}

	// enviroment factor for JUNO from FIDES
	float T_max = getDeviceTemperature() - component::KELVIN; // Highest Temperature of the PCB
	float pi_TV = 1;	// ambient temperature range. Temp < 110 = 1, Temp > 110 = e^(0.2(t_board-110)
	if( T_max >= 110 ){
		pi_TV = exp(0.2*( T_max - 110.));
	}
	//Cycling OFF
	float pi_Tcy_off = 0.6 * pi_TV * ( 12. * n_annual / t_annual ) * pow( ( delta_T / 20. ), 1.9 )* exp ( 1414 * ( 1 / ( component::KELVIN + 40 ) -( 1 / ( component::KELVIN + T_max ) ) ) );
	float pi_mech_off = 0.2 * pi_TV * pow( G_RMS / 0.5 , 1.5 );
	float pi_RH_off = 0.18 * pi_TV * pow( RH / 70. , 4.4 );
	float pi_chem_off = 0.02 * pi_TV * pi_sal * pi_evir * pi_zone * pi_prot;
	
	//Cycling ON
	float pi_Tcy_on = 0.6 * pi_TV * ( 12. * n_annual / ( 8760 - t_annual ) ) * pow( ( delta_T / 20. ), 1.9 )* exp ( 1414 * ( 1 / ( component::KELVIN + 40 ) -( 1 / ( component::KELVIN + T_max ) ) ) ); 	// Tmax correct here???
	float pi_mech_on = 0.2 * pi_TV * pow( G_RMS / 0.5 , 1.5 );
	float pi_RH_on = 0.18 * pi_TV * pow( RH / 70. , 4.4 );
	float pi_chem_on = 0.02 * pi_TV * pi_sal * pi_evir * pi_zone * pi_prot;

	//induced
	float pi_PM = exp( 1.39 * (1. - (QA_manufacturer + QA_component ) * E_risk / 24. )-0.69); 
	
	float pi_induced = pow( pi_placement * pi_application * pi_ruggedising , 0.511 * log(C_sensibility) );

	float lambda_physical = ( 8760. - t_annual ) / 8760. * ( pi_Tcy_on + pi_mech_on + pi_RH_on + pi_chem_on ) + t_annual / 8760. * ( pi_Tcy_off + pi_mech_off + pi_RH_off + pi_chem_off );
	
	return 5e-4 * sqrt(layers) * ( (float) connections / 2.) * ((float)viatech / 100.) * PCB_class * pi_PM * pi_process * lambda_physical * pi_induced;
}
