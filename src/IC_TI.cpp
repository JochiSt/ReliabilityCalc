#include "IC_TI.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

/// static sqlite3 handler with Read-Write Function
sqlite3_handler IC_TI::db = sqlite3_handler("./TI.db",SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

IC_TI::IC_TI(std::string name, std::string type) : IC_ELFR(name) {
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
    bool found = lookup_IC_DB();
    if(found){
	printf("... found in Database ");
    }else{
	printf("... not found in Database asking TI.com ");
	lookup_IC();
	store_in_DB();
    }
    printf(" ... result %4.1f @ %6.2f\n", FIT, FIT_temperature);
}

IC_TI::~IC_TI(){
    curl_easy_cleanup(curl);
}

void IC_TI::createTable(){
	std::string query = "CREATE TABLE ti_data ( partname VARCHAR(100), ELFR_DPPM DECIMAL(7,3), ELFR_CL  DECIMAL(7,3), ELFR_TestTemp DECIMAL(7,3), ELFR_SampleSize DECIMAL(7,3), ELFR_Failures DECIMAL(7,3), FIT_FIT DECIMAL(7,3), FIT_MTTF FLOAT, FIT_UsageTemp DECIMAL(7,3), FIT_CL DECIMAL(7,3), FIT_ActivationE DECIMAL(7,3), FIT_TestTemp DECIMAL(7,3), FIT_TestDuration DECIMAL(7,0), FIT_SampleSize INTEGER, FIT_Fails INTEGER );";

	db.runSQL(query);
};

void IC_TI::store_in_DB(){
    char query[4096];
    sprintf(query, "INSERT INTO ti_data VALUES ('%s', %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);",
				ICname.c_str(),
				results[0],  results[3],  results[4],  results[5],  results[6],
				results[2],  results[1],  results[7],  results[8],  results[9], 
				results[10], results[11], results[12], results[13]);
//    printf("%s\n", query);
    db.runSQL(std::string(query));
};

bool IC_TI::lookup_IC_DB(){
    char buffer[1024];
    std::string retvalue1 = "-", retvalue2 = "-", retvalue3 = "-";
    sprintf(buffer, "SELECT FIT_FIT, FIT_UsageTemp, ELFR_DPPM FROM ti_data WHERE partname = '%s'", ICname.c_str());
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

/**
 * lookup FIT value from TI's webpage
 * \warning since the internet access is needed, this function does not work offline
 */
void IC_TI::lookup_IC(){
    // ask TI webpage about this IC
    // aggregate FIT value from TI webpage
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30EA101SQ/NOPB#resultstable
    std::string data;

    char query[4096];
    sprintf(query, "http://www.ti.com/quality/docs/estimator.tsp?OPN=%s", ICname.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, query);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA    , &data);
    curl_easy_perform(curl);

    size_t start = data.find("<tbody>", data.find("resulttable")) + 7;
    size_t end   = data.find("</tbody>", start);
    data = data.substr( start, end - start);

    replace_all(data, "\r", "");
    replace_all(data, "\t", "");
    replace_all(data, "</tr>", "");
    replace_all(data, "<tr>", "");
    replace_all(data, "</td>", "");
    replace_all(data, "<td>", "");
    replace_all(data, "<td nowrap>", "");
    replace_all(data, "<sup>", "");
    replace_all(data, "</sup>", "");

    replace_all(data, "</a>", "");
    replace_all(data, "<", "");
    replace_all(data, "a", "");
    replace_all(data, ">", "");
    replace_all(data, "x 10", "E");
    replace_all(data, " ", "");

    std::string data_filtered;

    std::istringstream iss;
    iss.str(data);
    std::string line;
    unsigned int linepos = 0;
    while(true){
        getline(iss, line);
        if(!iss.good()) break;
        if(line.find("href") != std::string::npos) continue;
        if(line.length() >= 1){
            if(line.find("E") != std::string::npos && linepos > 0){
                data_filtered += line;
            }else{
                data_filtered += line + "\t";
            }
            linepos ++;
        }
    }

//    float ELFR_DPPM, MTBF, CL_EF, TT_EF, SS_EF, FD_EF, CL_FIT, E_FIT, TT_FIT, TD_FIT, SS_FIT, FD_FIT;

    // Part number 	ELFR-DPPM 	MTBF 	FIT 	Conf level (%) 	Test temp (°C)
    // Sample size 	Fails 	Usage temp (°C) 	Conf level (%) 	Activation energy (eV)
    // Test temp (°C) 	Test duration (hours) 	Sample size 	Fails

    std::string partnumber = data_filtered.substr(0, data_filtered.find("\t"));
    data_filtered = data_filtered.substr(data_filtered.find("\t")+1, std::string::npos);
//    std::cout <<"'"<< data_filtered <<"'"<< std::endl;

    char string[4096];
    sprintf(string, "%s", data_filtered.c_str() );
    char delimiter[] = "\t";
    char *ptr;

    // init and create first section
    ptr = strtok(string, delimiter);
    int section = 0;
    results.clear(); // clear result vector
    while(ptr != NULL) {
    	results.push_back( atof(ptr) );
    	ptr = strtok(NULL, delimiter);
    	section ++;
    }
    ELFR = results[0];
//    MTBF = results[1];
    FIT = results[2];
    FIT_temperature = results[7] + component::KELVIN;   // store temperature in KELVIN!

/*
    // print all received data
    printf("ELFR_DPPM\t%f\n", results[0]);
    printf("MTTF\t%f\n", results[1]);
    printf("FIT\t%f\n", results[2]);

    printf("\tEarly Failure Testing ...\n");
    printf("\t\tELFR-DPPM\t%f\n", results[0]);
    printf("\t\tConfidence Level:\t%.0f\n", results[3]);
    printf("\t\tTemperature:\t%.0f\n", results[4]);
    printf("\t\tSample Size\t%.0f\n", results[5]);
    printf("\t\tFailures\t%.0f\n", results[6]);

    printf("\tFIT ... \n");
    printf("\t\tFIT\t%f\n", results[2]);
    printf("\t\tMTTF\t%f\n", results[1]);
    printf("\t\tUsage Temperature\t%f\n", results[7]);
    printf("\t\tConfidence Level\t%f\n", results[8]);
    printf("\t\tActivation Energy\t%f\n", results[9]);
    printf("\t\tTest Temperature\t%f\n", results[10]);
    printf("\t\tTest duration\t%f\n", results[11]);
    printf("\t\tSample size\t%f\n", results[12]);
    printf("\t\tFails:\t%f\n", results[13]);
*/
}

