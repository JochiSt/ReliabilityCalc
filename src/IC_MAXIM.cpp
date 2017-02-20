#include "IC_MAXIM.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <map>

#include <stdio.h>
#include <stdlib.h>

IC_MAXIM::IC_MAXIM(std::string name, std::string type) : IC_DB(name, type) {

    bool found = lookup_IC_DB();
    if(found){
	printf("... found in Database ");
    }else{
	printf("... not found in Database asking maximintegrated.com ");
	fflush(stdout);
	lookupPartName();
	lookup_IC();
	store_in_DB();
    }
    printf(" ... result %4.1f @ %6.2f\n", FIT, FIT_temperature);
}

IC_MAXIM::~IC_MAXIM(){
}

// get right partname from TI's webpage
void IC_MAXIM::lookupPartName(){
}

/**
 * lookup FIT value from MAXIM's webpage
 * \warning since the internet access is needed, this function does not work offline
 */
void IC_MAXIM::lookup_IC(){
// first ask
// https://www.maximintegrated.com/en/qa/reliability/fit.cfm?upn=MAX232

    std::string data;
    char query[4096];
    sprintf(query, "https://www.maximintegrated.com/en/qa/reliability/fit.cfm?upn=%s", ICname.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, query);
//    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
//    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, IC_DB::curl_writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA    , &data);
    curl_easy_perform(curl);

    data = data.substr(data.find("/en/qa/reliability/fit.cfm"), std::string::npos);
    data = data.substr(0, data.find("</table>"));

    std::string search = "<td class=\"tablebody3\">";
    data = data.substr(data.find(search)+search.length(), std::string::npos);

    replace_all(data, "\r", "");
    replace_all(data, "\n", "");
    replace_all(data, "\t", "");

    replace_all(data, "<td class=\"tablebody3\">", "");
    replace_all(data, "</td>", "\t\t");
    replace_all(data, "<tr>", "");
    replace_all(data, "</tr>", "\n");

//    printf("Device  Fab Process	    Technology	Sample Size	Rejects	    FIT @25°C	FIT @55°C\n");
//    printf("%s\n", data.c_str());

    std::map<std::string, ic_data_t> maxim_map;
   
    std::istringstream iss;
    iss.str(data.c_str());

    std::string device_name, fab_process, technology;
    int sample_size, rejects;
    float FIT25, FIT55;

    while(true){
	iss >> device_name >> fab_process >> technology >> sample_size >> rejects >> FIT25 >> FIT55;
	if(!iss.good())
	    break;

	maxim_data.sample_size = sample_size;
	maxim_data.rejects = rejects;
	maxim_data.FIT_25 = FIT25;
	maxim_data.FIT_55 = FIT55;

	std::string index = fab_process + std::string("_") + technology;
	
	maxim_map[index] = maxim_data;	
    } 

    if(maxim_map.size() > 1){
	printf("\n\tfound more than one dataset\n");
	printf("\tassuming highest FIT unless part better specified\n");
    }
    float maxFIT25 = 0;
    int maxSampleSize = 0;
    int maxRejects = 0;
    for (std::map<std::string, ic_data_t>::iterator it=maxim_map.begin(); it!=maxim_map.end(); ++it){
	if(maxim_map.size() > 1){
	    std::cout << "\t\t" << it->first << " => " << (it->second).FIT_25 << '\n'; 
	}
        if(maxFIT25 < (it->second).FIT_25){
	    maxFIT25 = (it->second).FIT_25;
	    maxSampleSize = (it->second).sample_size;
	    maxRejects = (it->second).rejects;
        }
    }
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
*/
    results[2] =maxFIT25;
/*
    printf("\t\tMTTF\t%f\n", results[1]);
    printf("\t\tUsage Temperature\t%f\n", results[7]);
*/
    results[7] = 25;
/*
    printf("\t\tConfidence Level\t%f\n", results[8]);
    printf("\t\tActivation Energy\t%f\n", results[9]);
    printf("\t\tTest Temperature\t%f\n", results[10]);
    printf("\t\tTest duration\t%f\n", results[11]);
*/
//    printf("\t\tSample size\t%f\n", results[12]);
    results[12] = maxSampleSize;
//    printf("\t\tFails:\t%f\n", results[13]);
    results[13] = maxRejects;

    FIT = results[2];
    FIT_temperature = results[7] + component::KELVIN;   // store temperature in KELVIN!
}

