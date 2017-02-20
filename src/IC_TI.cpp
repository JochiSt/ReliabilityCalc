#include "IC_TI.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

IC_TI::IC_TI(std::string name, std::string type) : IC_DB(name, type) {

    bool found = lookup_IC_DB();
    if(found){
	printf("... found in Database ");
    }else{
	printf("... not found in Database asking TI.com ");
	lookupPartName();
	lookup_IC();
	store_in_DB();
    }
    printf(" ... result %4.1f @ %6.2f\n", FIT, FIT_temperature);
}

IC_TI::~IC_TI(){
}

// get right partname from TI's webpage
void IC_TI::lookupPartName(){
// first ask
// http://www.ti.com/quality/docs/estimator.tsp?partType=tiPartNumber&partNumber=DS15BA101
    std::string data;
    char query[4096];
    sprintf(query, "http://www.ti.com/quality/docs/estimator.tsp?partType=tiPartNumber&partNumber=%s", ICname.c_str());


    curl_easy_setopt(curl, CURLOPT_URL, query);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA    , &data);
    curl_easy_perform(curl);

    if(data.find("No results found. Please enter another search criteria") != std::string::npos){
	fprintf(stderr, "IC (%s) not found on TI website.\n", ICname.c_str());
	fprintf(stderr, "using query ... \n");
    	fprintf(stderr, "%s\n", query);
	fprintf(stderr, "exiting ...\n");
	exit(-1);
    }
    if(data.find("possible matches. Please choose a") != std::string::npos){
	size_t start = data.find("<ul class=\"resultsList\">")+24;
	size_t end   = data.find("</div>", start);
	data = data.substr( start, end - start);

	replace_all(data, "\r", "");
	replace_all(data, "\n", "");
	replace_all(data, "\t", "");

	start = data.find(">")+1;
	end   = data.find("<", start);

	data = data.substr(start, end-start);

	printf(" ... partname '%s' ", data.c_str());

	ICname = data;
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

