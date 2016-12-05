#include "IC_TI.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>


IC_TI::IC_TI(std::string name, std::string type) : IC_ELFR(name) {
    ICname = type;

    curl_global_init(CURL_GLOBAL_WIN32);
    curl = curl_easy_init();
    if(!curl)
	exit(1);

    lookup_IC();
}

IC_TI::~IC_TI(){
    curl_easy_cleanup(curl);
}

/**
 * lookup FIT value from TI's webpage
 * \warning since the internet access is needed, this function does not work offline
 */
void IC_TI::lookup_IC(){
    // ask TI webpage about this IC
    // aggregate FIT value from TI webpage
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30EA101SQ/NOPB#resultstable
    printf("Asking TI about ... %s ", ICname.c_str());
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
    std::vector<float> results;
    while(ptr != NULL) {
    	results.push_back( atof(ptr) );
    	ptr = strtok(NULL, delimiter);
    	section ++;
    }
    ELFR = results[0];
//    MTBF = results[1];
    FIT = results[2];
    FIT_temperature = results[7] + component::KELVIN;   // store temperature in KELVIN!

//    printf("Determined FIT %f @ %f °C\n", FIT, FIT_temperature);

    printf(" ... result %f @ %f\n", FIT, FIT_temperature);
}

