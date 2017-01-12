#include "component.h"
#include <stdlib.h>
#include <stdio.h>

// init static variables

float component::ambientTemperature = 40 + component::KELVIN;           // init to 40°C
std::string component::FITunit = "1E9 h";
unsigned int component::partcnt = 0;

/// static sqlite3 handler with Read-Only Function
sqlite3_handler component::TempDB = sqlite3_handler("./temperatures.db");

component::component(std::string val){
	name = val;				// save the name e.g. U100
	deviceTemperature = 0.;			// no device temperature has been set
	deviceDeltaT = 0;
	if(TempDB.getStatus()){
		deviceDeltaT = getDeviceTincrease();	// have a look at the DB, whether there is some 
							// deltaT for this device stored
	}
}

float component::getDeviceTincrease(){
    char buffer[1024];
    std::string retvalue1 = "-", retvalue2 = "-";
    sprintf(buffer, "SELECT deltaT FROM Tincrease WHERE partname = '%s'", name.c_str());
    TempDB.runSQL(std::string(buffer), retvalue1);
    if(retvalue1 == "-"){
	return 0.;
    }else{
	float deltaT = atof( retvalue1.c_str());
	printf("%s found deltaT = %3.2f in database\n", name.c_str(), deltaT);
	return deltaT; 
    }	
}
