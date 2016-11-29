#include "schematic.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <numeric>
#include <sstream>

#include "diode.h"
#include "resistor.h"
#include "capacitor.h"
#include "IC.h"
#include "inductor.h"

schematic::schematic(std::string name) : component(name){
    verbose_output = false;
    //ctor
}

float schematic::getFIT(){
    if(verbose_output){
        std::cout << "Calculating FIT for " << name << std::endl;
    }
    float FIT = 0;
    for(unsigned int i = 0; i < parts.size(); i++ ){
        float partFIT = parts.at(i) -> getFIT();
        if(verbose_output) {
                std::cout << "  " << std::setw(20) << parts.at(i)->getName() << "\t" << std::setprecision(7)  << std::setw(12) << partFIT << " / " << component::FITunit << std::endl;
        }
        FIT += partFIT;
    }
    if(verbose_output){
        std::cout << "total FIT: " << FIT << std::endl;
    }
    return FIT;
}

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

float schematic::getFailureRate(float deviceHours, double FIT, float weibullExponent){
    return 1. - exp( -1. * std::pow(FIT / 1E6 * deviceHours, weibullExponent) );
}

float schematic::getFailureRateError(float deviceHours, double FIT, float weibullExponent, float weibullExponentError){
    // https://www.wolframalpha.com/input/?i=D%5B1+-+Exp%5B-(f+*+t)%5Em%5D,+m%5D
    return std::abs(exp( -1. * std::pow(FIT / 1E6 * deviceHours, weibullExponent) ) *
                    std::pow(FIT / 1E6 * deviceHours, weibullExponent) *
                    std::log(FIT / 1E6 * deviceHours) *
                    weibullExponentError);
}

void schematic::printPartCount(){
    std::cout << "parts used to calculate reliability "<< std::endl;
    std::cout << "\t" << diode::getPartCount() << " Diodes" << std::endl;
    std::cout << "\t" << resistor::getPartCount() << " Resistors" << std::endl;
    std::cout << "\t" << capacitor::getPartCount() << " Capacitors" << std::endl;
    std::cout << "\t" << IC::getPartCount() << " ICs" << std::endl;
    std::cout << "\t" << inductor::getPartCount() << " inductors" << std::endl;
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

