#include "component.h"

// init static variables

float component::ambientTemperature = 40 + component::KELVIN;           // init to 40°C
std::string component::FITunit = "1E9 h";
unsigned int component::partcnt = 0;

component::component(std::string val){
    name = val;
}
