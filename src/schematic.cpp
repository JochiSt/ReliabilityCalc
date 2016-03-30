#include "schematic.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "resistor.h"
#include "capacitor.h"
#include "inductor.h"
#include "IC.h"
#include "diode.h"

schematic::schematic(std::string name) : component(name){
    //ctor
}

float schematic::getFIT(){
    std::cout << "Calculating FIT for " << name << std::endl;
    double FIT = 0;
    for(unsigned int i = 0; i < parts.size(); i++ ){
        FIT += parts.at(i) -> getFIT();
    }
    std::cout << std::endl;
    return FIT;
}

float schematic::getFailureRate(float deviceHours, double FIT){
    return 1. - exp( -1. * FIT / 1E6 * deviceHours );
}

void schematic::exportToFile(std::string filename){
    std::cout << std::endl << std::endl;
    std::cout << "Exporting to: " << filename << std::endl;
    std::ofstream outF;
    outF.open(filename.c_str());
    for(unsigned int i = 0; i< parts.size(); i++){
 //           std::cout << i << "\t" << parts.at(i)->toString() << std::endl;
            outF << i << "\t" << parts.at(i)->toString() << std::endl;
    }
    outF.close();
}

void schematic::importFromFile(std::string filename){
    std::cout << "Importing from: " << filename << std::endl;
    std::ifstream inF;
    inF.open(filename.c_str());
    std::string line;
    int cnt = 0;
    int linecnt;
    std::string identifier;
    while(true){
        std::getline(inF, line);
        if(!inF.good()) break;

        std::istringstream iss;
        iss.str(line);
        iss >> linecnt >> identifier;
        if(linecnt != cnt){
            std::cerr << "Oops, something wrent wrong" << std::endl;
            std::cerr << "\tlinecounter mismatch" << std::endl;
            break;
        }

        if(identifier == resistor::getIdentifier() ){
            addComponent(new resistor());
            if( lastAddedComponent() -> fromString( line.substr( line.find(resistor::getIdentifier()), std::string::npos) ) < 0 ){
                    std::cerr << "unable to add component" << std::endl;
                    removeLastComponent();
            }
        }else if(identifier == capacitor::getIdentifier() ){
            addComponent(new capacitor());
            if( lastAddedComponent() -> fromString( line.substr( line.find(capacitor::getIdentifier()), std::string::npos) ) < 0){
                    std::cerr << "unable to add component" << std::endl;
                    removeLastComponent();
            }
        }else if(identifier == "U"){
            addComponent(new IC());
            if( lastAddedComponent() -> fromString( line.substr( line.find(IC::getIdentifier()), std::string::npos) ) < 0){
                    std::cerr << "unable to add component" << std::endl;
                    removeLastComponent();
            }
        }else if(identifier == "L"){
            addComponent(new inductor());
            if( lastAddedComponent() -> fromString( line.substr( line.find(inductor::getIdentifier()), std::string::npos) ) < 0){
                    std::cerr << "unable to add component" << std::endl;
                    removeLastComponent();
            }
        }else if(identifier == "D"){
            addComponent(new diode());
            if( lastAddedComponent() -> fromString( line.substr( line.find(diode::getIdentifier()), std::string::npos) ) < 0){
                    std::cerr << "unable to add component" << std::endl;
                    removeLastComponent();
            }
        }else{
            std::cerr << "Oops, something went wrong" << std::endl;
            std::cerr << "\tidentifier '" << identifier << "' unknown" << std::endl;
            break;
        }
        cnt ++;
    }
}

float schematic::getAccelerationFactor(float testT, float refT){
    float deviceHours = 1E6;
    float AF = getFailureRate(deviceHours, getFIT(testT)) / getFailureRate(deviceHours, getFIT(refT));
    return AF;
}

void schematic::temperatureScan(int points, float startT, float stopT, std::vector<float> &temp, std::vector<float> &FIT){
    // clear vectors
    temp.clear();
    FIT.clear();

    float tempT = getAmbientTemperature();

    for(float T = startT; T<= stopT; T += (stopT - startT)/(float)points ){
        FIT.push_back( getFIT(T) );
        temp.push_back(T);
    }

    setAmbientTemperature(tempT);
}

void schematic::exportDataToFile(std::string filename, std::vector<float> vec1, std::vector<float>vec2){
    std::ofstream output;
    output.open(filename.c_str());
    for(unsigned int i=0; ( i < vec1.size() && i < vec2.size() ); i++ ){
        output << vec1[i] << "\t" << vec2[i] << std::endl;
    }
    output.close();
}

