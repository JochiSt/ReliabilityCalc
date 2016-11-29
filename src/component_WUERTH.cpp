
#include "component_WUERTH.h"

sqlite3_handler component_WUERTH::db = sqlite3_handler("./wuerth.db");

component_WUERTH::component_WUERTH(std::string code){
	matchcode = code;

	// init values from table with nothing
	FIT_table = "-";
	FIT_curve = '-';
	SIGMA_table = "-";
	SIGMA_curve = '-';
}
