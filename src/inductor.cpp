#include "inductor.h"

#include <iostream>
#include <cmath>
#include <sstream>

std::string inductor::identifier = "L";
unsigned int inductor::partcnt = 0;

inductor::inductor(std::string name) : component(name){
    partcnt++;
}

inductor::~inductor(){
    partcnt--;
};
