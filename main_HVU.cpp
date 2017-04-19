#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor_WUERTH.h"
#include "resistor_VISHAY_CRCWe3.h"
#include "IC_TI.h"
#include "IC_AD.h"
#include "IC_MAXIM.h"
#include "inductor_WUERTH.h"
#include "diode.h"
#include "PCB.h"

#include "utils.h"

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl << endl;

    cout << "FIT for 0.5% in 6 years " << utils::FailureRate2FIT(0.5/100., 6*365*24.) << endl;

    component::setAmbientTemperature(45);

    schematic* HVU = new schematic("High Voltage Unit");

    HVU -> addComponent( new IC_TI("U2", "LP2981-50DBVT"));
    HVU -> addComponent( new IC_TI("U3", "REF3033"));
    HVU -> addComponent( new IC_TI("U4", "LMC555CMM"));

    HVU -> addComponent( new IC_AD("U5", "AD8603"));
    HVU -> addComponent( new IC_AD("U6", "AD8603"));

    HVU -> addComponent( new IC_MAXIM("U7", "MAX3471EUA"));
    

    
    HVU -> setVerboseOutput(true);  // enable verbose output
    HVU -> getFIT();

    return 0;
}
