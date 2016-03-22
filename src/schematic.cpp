#include "schematic.h"

#include <iostream>
#include <cmath>

schematic::schematic(std::string name) : component(name){
    //ctor
}

schematic::~schematic(){
    //dtor
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
    for(unsigned int i = 0; i< parts.size(); i++){
            std::cout << i << "\t" << parts.at(i)->toString() << std::endl;
    }
}

void schematic::importFromFile(std::string filename){
    std::cout << "Importing from: " << filename << std::endl;
}
