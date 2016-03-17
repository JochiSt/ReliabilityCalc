#include "schematic.h"

#include <iostream>

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

    return FIT;
}

float schematic::getFailureRate(float deviceHours){
    double FIT = getFIT();
    return FIT;
}
