#include <stdio.h>
#include <stdlib.h>

#include "component_WUERTH.h"
#include "component.h"

sqlite3_handler component_WUERTH::db = sqlite3_handler("./wuerth.db");

component_WUERTH::component_WUERTH(std::string code){
	matchcode = code;

// just for testing
	std::string NumberDataSets;
	db.runSQL("SELECT COUNT(*) FROM MatchCodeMapping", NumberDataSets);
	printf("found %s types in component WUERTH lookup table\n", NumberDataSets.c_str());

	// init values from table with nothing
	FIT_table = "-";
	FIT_curve = '-';
	SIGMA_table = "-";
	SIGMA_curve = '-';

	searchTable();	// have a look at the database
}

void component_WUERTH::searchTable(){
	std::string Ftable;
	std::string Fcurve;
	std::string Stable;
	std::string Scurve;

	std::string query = "SELECT FITtable, FITcurve, SIGMAtable, SIGMAcurve FROM MatchCodeMapping WHERE matchcode = '" + matchcode + "' LIMIT 1";
	// printf("\t'%s'\n", query.c_str());

	db.runSQL(query, Ftable, Fcurve, Stable, Scurve);

	FIT_table = Ftable;
	FIT_curve = Fcurve[0];
	SIGMA_table = Stable;
	SIGMA_curve = Scurve[0];
}

void component_WUERTH::getFIT(float temperature, float &retTempL, float &FITL, float &retTempU, float&FITU, char curve){
	std::string retvalue1 = "-1", retvalue2 = "-1";
	char buffer[2048];

	char usedCurve = FIT_curve;
	if(curve != '-')
		usedCurve = curve;

	sprintf(buffer, "SELECT temperature, FIT FROM reliability_data WHERE temperature <= '%5.2f' AND ('table' - %s)<0.01 AND curve = '%c' ORDER BY temperature DESC LIMIT 1",
								temperature-component::KELVIN, FIT_table.c_str(), usedCurve);

	db.runSQL(std::string(buffer), retvalue1, retvalue2);

	retTempL = atof(retvalue1.c_str()) + component::KELVIN;
	FITL = atof(retvalue2.c_str());

	sprintf(buffer, "SELECT temperature, FIT FROM reliability_data WHERE temperature > '%5.2f' AND ('table' - %s)<0.01 AND curve = '%c' ORDER BY temperature ASC LIMIT 1",
								temperature-component::KELVIN, FIT_table.c_str(), usedCurve);

	db.runSQL(std::string(buffer), retvalue1, retvalue2);

	retTempU = atof(retvalue1.c_str()) + component::KELVIN;
	FITU = atof(retvalue2.c_str());
}
