#include "IC_AD.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <map>

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

IC_AD::IC_AD(std::string name, std::string type) : IC_DB(name, type) {

    bool found = lookup_IC_DB();
    if(found){
	printf("... found in Database ");
    }else{
	printf("... not found in Database asking analog.com ");
	fflush(stdout);
	lookupPartName();
	lookup_IC();
	
	if( FIT > 1000 ){
	    fprintf(stderr, "seems, that IC was not found\n");
	    exit(-1);
	}

	store_in_DB();
    }
    printf(" ... result %4.2f @ %6.2f\n", FIT, FIT_temperature);
}

IC_AD::~IC_AD(){
}

// get right partname from TI's webpage
void IC_AD::lookupPartName(){
}

/**
 * lookup FIT value from MAXIM's webpage
 * \warning since the internet access is needed, this function does not work offline
 */
void IC_AD::lookup_IC(){
// first ask
// http://www.analog.com/reliabilitydata/RD_WaferFab_Results.aspx?productid=ADP1765&productvalue=ADP1765
// http://www.analog.com/reliabilitydata/RD_WaferFab_Results.aspx?productvalue=ADP1765 
// works as well, but needs one less parameter

    std::string data;
    char query[4096];
    sprintf(query, "http://www.analog.com/reliabilitydata/RD_WaferFab_Results.aspx?productvalue=%s", ICname.c_str() );

    curl_easy_setopt(curl, CURLOPT_URL, query);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, IC_DB::curl_writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA    , &data);
    curl_easy_perform(curl);

    data = data.substr(data.find("<div id=\"ProcessTech\">"), std::string::npos);
    data = data.substr(0, data.find("To recalculate"));

//    replace_all(data, "\r", "");
    replace_all(data, "\n", "");

    replace_all(data, "<b>", "");
    replace_all(data, "</b>", "");

    replace_all(data, "<strong>", "");
    replace_all(data, "</strong>", "");
    
    replace_tag(data, "span", "");
    replace_tag(data, "table", "");
    replace_tag(data, "div", "");
    replace_tag(data, "td", "");
    replace_tag(data, "tr", "");

    replace_all(data, "</tr>", "\n");
    replace_all(data, "</span>", "");
    replace_all(data, "</td>", "\t");
    replace_all(data, "</div>", "");
    replace_all(data, "</form>", "");

    replace_all(data, " ", "");
    replace_all(data, "0.", " 0,");
    replace_all(data, ".", "");
    replace_all(data, "0,", " 0.");
    replace_all(data, "@", " ");
    replace_all(data, "degC", " ");
    replace_all(data, "eV", " ");
    replace_all(data, ")", "");
    replace_all(data, "(", "");

    std::istringstream iss;
    std::istringstream iss2;
    iss.str(data.c_str());

    std::string text;
    double value1, value2;

    std::string line;
    while(true){
	if(!iss.good()) break;	
	getline(iss, line); 

	iss2.str(line);	

	if( line.find("OverallSampleSize") != std::string::npos ){
	    iss2 >> text >> value1;
	    results[12] = value1;	    
	}else if( line.find("QtyFail") != std::string::npos ){
	    iss2 >> text >> value1;
	    results[13] = value1;
	}else if( line.find("EquivalentDeviceHrs") != std::string::npos ){
	    iss2 >> text >> value1 >> value2;
	    results[11] = value2;
	    results[7] = value1;
	}else if( line.find("ActivationEnergy") != std::string::npos ){
	    iss2 >> text >> value1 >> text;
	    results[9] = value1;
	}	
    }

    results[8] = 0.6;	// set to 60% confidence level
    // calculate FIT from data
    results[2] = utils::calcFIT(results[8], results[13], results[11]); 

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
//    results[2] =maxFIT25;
/*
    printf("\t\tMTTF\t%f\n", results[1]);
    printf("\t\tUsage Temperature\t%f\n", results[7]);
*/
//    results[7] = 25;
/*
    printf("\t\tConfidence Level\t%f\n", results[8]);
    printf("\t\tActivation Energy\t%f\n", results[9]);
    printf("\t\tTest Temperature\t%f\n", results[10]);
    printf("\t\tTest duration\t%f\n", results[11]);
*/
//    printf("\t\tSample size\t%f\n", results[12]);
//    results[12] = maxSampleSize;
//    printf("\t\tFails:\t%f\n", results[13]);
//    results[13] = maxRejects;

    FIT = results[2];
    FIT_temperature = results[7] + component::KELVIN;   // store temperature in KELVIN!
}

