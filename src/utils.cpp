#include "utils.h"
#include <cmath>
#include <stdio.h>
#include <gsl/gsl_cdf.h>

float utils::FIT2FailureRate(float FIT, float deviceHours){
	return 1. - exp( -1. * FIT / 1E9 * deviceHours);
}
float utils::FailureRate2FIT(float failureRate, float deviceHours){
	return -1. * log(1. - failureRate) / deviceHours * 1E9;
}

float utils::calcFIT(float conflevel, int failures, double devhours){
    double FIT = 10000;
    #ifdef __GSL_CDF_H__
/*
    printf("confidence level %f\n", conflevel);
    printf("failures %f\n", 2.*failures+2);
    printf("chi2 %lf\n", gsl_cdf_chisq_Pinv(conflevel, 2*failures+2));
    printf("devhours %lf\n", devhours);    
*/
    FIT = 1E9 * gsl_cdf_chisq_Pinv(conflevel, 2*failures+2) / 2. / devhours;
    #endif
    return FIT;	    
}



void utils::temperatureScan(schematic* schematic, std::vector<float> temperatures, std::vector<float> &FIT){

    FIT.clear();
    
    bool verboseOutput = schematic -> getVerboseOutput();
    schematic->setVerboseOutput(false);	// we want a quiet function

    for(unsigned int i=0; i < temperatures.size(); i++){
	schematic -> setAmbientTemperature( temperatures[i] );
	FIT.push_back( schematic -> getFIT() );

    }

    schematic -> setVerboseOutput( verboseOutput );
}
