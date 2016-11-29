#include <stdio.h>
#include <stdlib.h>


#include "component_WUERTH.h"

sqlite3_handler component_WUERTH::db = sqlite3_handler("./wuerth.db");

component_WUERTH::component_WUERTH(std::string code){
	matchcode = code;

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
