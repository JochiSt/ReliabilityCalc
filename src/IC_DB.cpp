#include "IC_DB.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

/// static sqlite3 handler with Read-Write Function
sqlite3_handler IC_DB::db = sqlite3_handler("./ICoffline.db",SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

IC_DB::IC_DB(std::string name, std::string type) : IC_ELFR(name) {
    ICname = type;

    curl_global_init(CURL_GLOBAL_WIN32);
    curl = curl_easy_init();
    if(!curl)
	exit(1);

    printf("Looking up ... %s ", ICname.c_str());

    if(!db.existsTable("ti_data")){
	printf("... table not found - creating database ");
	createTable();
    }
}

IC_DB::~IC_DB(){
    curl_easy_cleanup(curl);
}

bool IC_DB::lookup_IC_DB(){
    char buffer[1024];
    std::string retvalue1 = "-", retvalue2 = "-", retvalue3 = "-";
    sprintf(buffer, "SELECT FIT_FIT, FIT_UsageTemp, ELFR_DPPM FROM ti_data WHERE partname LIKE '%s%c'", ICname.c_str(), '%');
    db.runSQL(std::string(buffer), retvalue1, retvalue2);
    if(retvalue1 == "-"){
	return false;
    }else{
	FIT = atof(retvalue1.c_str());
	FIT_temperature = atof(retvalue2.c_str()) + component::KELVIN;	
	ELFR = atof(retvalue3.c_str());
	return true;
    }
}

void IC_DB::createTable(){
	std::string query = "CREATE TABLE ti_data ( partname VARCHAR(100), ELFR_DPPM DECIMAL(7,3), ELFR_CL  DECIMAL(7,3), ELFR_TestTemp DECIMAL(7,3), ELFR_SampleSize DECIMAL(7,3), ELFR_Failures DECIMAL(7,3), FIT_FIT DECIMAL(7,3), FIT_MTTF FLOAT, FIT_UsageTemp DECIMAL(7,3), FIT_CL DECIMAL(7,3), FIT_ActivationE DECIMAL(7,3), FIT_TestTemp DECIMAL(7,3), FIT_TestDuration DECIMAL(7,0), FIT_SampleSize INTEGER, FIT_Fails INTEGER );";

	db.runSQL(query);
};

void IC_DB::store_in_DB(){
    char query[4096];
    sprintf(query, "INSERT INTO ti_data VALUES ('%s', %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);",
				ICname.c_str(),
				results[0],  results[3],  results[4],  results[5],  results[6],
				results[2],  results[1],  results[7],  results[8],  results[9], 
				results[10], results[11], results[12], results[13]);
//    printf("%s\n", query);
    db.runSQL(std::string(query));
};

