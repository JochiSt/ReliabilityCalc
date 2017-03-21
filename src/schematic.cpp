#include "schematic.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <numeric>
#include <sstream>

#include "utils.h"

#include "diode.h"
#include "resistor.h"
#include "capacitor.h"
#include "IC.h"
#include "inductor.h"

#include <time.h>

#define FIT_PRECISION	4
#define FIT_WIDTH	10
#define SPACE_WIDTH	3
#define INDENTION	20

schematic::schematic(std::string name) : component(name){
    // for MC calculations, we need a random number generator
    srand(time(NULL));
    verbose_output = false;

    MCsoftErrorTol = 2;
}

float schematic::getFIT(){
    if(verbose_output){
        std::cout << "Calculating FIT for " << name << std::endl;
    }
    float FIT = 0;
    for(unsigned int i = 0; i < parts.size(); i++ ){
	unsigned int partCNT = part_count.at(i);
        float partFIT = parts.at(i) -> getFIT();
	float totalFIT = partFIT * partCNT;
        if(verbose_output) {
            std::cout << "  " << std::setw(INDENTION) << parts.at(i)->getName();
	    std::cout << std::setw(SPACE_WIDTH) << " ";
	    std::cout << std::fixed << std::setprecision(FIT_PRECISION)  << std::setw(FIT_WIDTH) << totalFIT;
	    std::cout << " / " << component::FITunit;
	    if(partCNT > 1){
	        std::cout << " " << std::setw(4) << std::fixed << partCNT << " pcs. ";
	        std::cout << " each ";
                std::cout << std::fixed << std::setprecision(FIT_PRECISION)  << std::setw(FIT_WIDTH) << partFIT;
	    }
            std::cout << std::endl;
        }
        FIT += totalFIT;
    }
    if(verbose_output){
	std::cout << "  " << std::setw(INDENTION+SPACE_WIDTH) << " " << "-----------" << std::endl;
	std::cout << "  " << std::setw(INDENTION) << "total FIT:";
	std::cout << std::setw(SPACE_WIDTH) << " ";
	std::cout << std::fixed << std::setprecision(FIT_PRECISION) << std::setw(FIT_WIDTH) << FIT;
	std::cout << " / " << component::FITunit << std::endl;
    }
    return FIT;
}

/*
float schematic::estimateWeibullExponent(float earlyLifetimeHours){
    return estimateWeibullExponent(earlyLifetimeHours, MEAN);
}

float schematic::estimateWeibullExponent(float earlyLifetimeHours, estimation_t type){
    std::vector<float> validWeibullExponents;
    for (std::vector<component*>::iterator part = parts.begin(); part != parts.end(); ++part){
        float m = (*part)->estimateWeibullExponent(earlyLifetimeHours);
        if (m >= 0.){
            std::cout << "Weibull exponent for " << (*part)->getName() << " is " << m << "." << std::endl;
            validWeibullExponents.push_back(m);
        }
    }

    if (type == MINIMUM){
        return *std::min_element(validWeibullExponents.begin(), validWeibullExponents.end());
    } else if (type == MAXIMUM){
        return *std::max_element(validWeibullExponents.begin(), validWeibullExponents.end());
    } else {
        float mean = std::accumulate(validWeibullExponents.begin(), validWeibullExponents.end(), 0.) / validWeibullExponents.size();
        if (type == MEAN){
            return mean;
        } else {
            float stddev = 0.;
            for (std::vector<float>::iterator m = validWeibullExponents.begin(); m != validWeibullExponents.end(); ++m){
                stddev += (*m - mean)*(*m - mean);
            }
            stddev = std::sqrt(stddev / (validWeibullExponents.size() - 1.));
            return stddev;
        }
    }
    return -1.;
}
*/
/*

float schematic::getFailureRateError(float deviceHours, double FIT, float weibullExponent, float weibullExponentError){
    // https://www.wolframalpha.com/input/?i=D%5B1+-+Exp%5B-(f+*+t)%5Em%5D,+m%5D
    return std::abs(exp( -1. * std::pow(FIT / 1E6 * deviceHours, weibullExponent) ) *
                    std::pow(FIT / 1E6 * deviceHours, weibullExponent) *
                    std::log(FIT / 1E6 * deviceHours) *
                    weibullExponentError);
}
*/
void schematic::printPartCount(){
    std::cout << "parts used to calculate reliability "<< std::endl;
    std::cout << "\t" << std::setw(5) << diode::getPartCount() << " Diodes" << std::endl;
    std::cout << "\t" << std::setw(5) << resistor::getPartCount() << " Resistors" << std::endl;
    std::cout << "\t" << std::setw(5) << capacitor::getPartCount() << " Capacitors" << std::endl;
    std::cout << "\t" << std::setw(5) << IC::getPartCount() << " ICs" << std::endl;
    std::cout << "\t" << std::setw(5) << inductor::getPartCount() << " inductors" << std::endl;
    
    int partsum = diode::getPartCount() + resistor::getPartCount() + capacitor::getPartCount();
        partsum+= IC::getPartCount() + inductor::getPartCount();

    std::cout << "\t-----" << std::endl;
    std::cout << "\t" << std::setw(5) << partsum << " parts in total" << std::endl;
}

float schematic::getAccelerationFactor(float testT, float refT){
    float fitTest = getFIT(testT, false);
    float fitRef = getFIT(refT, false);

    return fitTest / fitRef;
}

void schematic::temperatureScan(int points, float startT, float stopT, std::vector<float> &temp, std::vector<float> &FIT){
    // clear vectors
    temp.clear();
    FIT.clear();

    float tempT = getAmbientTemperature();

    for(float T = startT; T<= stopT; T += (stopT - startT)/(float)points ){
        FIT.push_back( getFIT(T, false) );
        temp.push_back(T);
    }

    setAmbientTemperature(tempT);
}

void schematic::temperatureScanAF(int points, float startT, float stopT, std::vector<float> &temp, std::vector<float> &AF){
    // clear vectors
    temp.clear();
    AF.clear();

    float tempT = getAmbientTemperature();

    for(float T = startT; T<= stopT; T += (stopT - startT)/(float)points ){
        AF.push_back( getAccelerationFactor( T, tempT ) );
        temp.push_back(T);
    }

    setAmbientTemperature(tempT);
}

float schematic::getFIT(float temperature, bool output){
    if(temperature < KELVIN){
        temperature += KELVIN;
    }
    float tempT = getAmbientTemperature();
    setAmbientTemperature(temperature);
    float FIT = getFIT(output);
    setAmbientTemperature(tempT);
    return FIT;
}

void schematic::exportDataToFile(std::string filename, std::vector<float> vec1, std::vector<float>vec2){
    std::ofstream output;
    output.open(filename.c_str());
    for(unsigned int i=0; ( i < vec1.size() && i < vec2.size() ); i++ ){
        output << vec1[i] << "\t" << vec2[i] << std::endl;
    }
    output.close();
}

/******************************************************************************
 * Monte Carlo FIT calculation
 *	    using failure probabilities and can still cause mission to suceed
 *	    with some errors
 */
void schematic::MCcalculateFIT(double runtime, unsigned long int tries){
    double cntALL = 0;	// sum of all errors
    double cntFMD = 0;	// sum of errors, which cause mission to fail
 
    // do multiple simulations
    for(unsigned int run = 0; run < tries; run ++){
	unsigned int softFailureCNT = 0;    // sum of all small errors
	bool missionFail = false;	    // mission critical error happened
	bool partFail = false;		    // part failure according to FIT

	// loop over all components of this schematic
	for(unsigned int cmp = 0; cmp < parts.size(); cmp ++){

	    double partFailureProb = utils::FIT2FailureRate(parts[cmp] -> getFIT(), runtime);
	    double partFailure = rand(); partFailure /= RAND_MAX;

	    // is this part failing ?
	    if( partFailure < partFailureProb ){    // if true part has been failed
		partFail = true;		    // there has been some failure observed
		
		// if failing -> have a look at the failure mode
	    	double failureMode = rand(); failureMode /= RAND_MAX;
	   
		// TODO FIXME insert right failure mode prob here 
		if( 0.5 > failureMode || part_critical[cmp] ){	// component seriously failed
		    missionFail = true;				// or component really important for mission
                }else{
		    softFailureCNT ++;				// SoftFailure, which might still cause mission to succeed
		}
    	    }
	} 
	// ANALYSIS of the failures
	if( partFail ){
	    cntALL ++;	
	    if( missionFail || softFailureCNT > MCsoftErrorTol ){
		// either mission critical failure or too many soft failures
		cntFMD ++;
	    } 
	}
    }   

    cntALL /= tries;
    cntFMD /= tries;

    double FITall = utils::FailureRate2FIT(cntALL, runtime); 
    double FITfmd = utils::FailureRate2FIT(cntFMD, runtime); 
    
    printf("ALL %lf FIT \t\t FMD %lf FIT\n", FITall, FITfmd);

}

