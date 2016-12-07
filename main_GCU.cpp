#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor.h"
#include "resistor.h"
#include "resistor_VISHAY_CRCWe3.h"
#include "IC.h"
#include "inductor.h"
#include "diode.h"

#include "capacitor_WUERTH.h"
#include "inductor_WUERTH.h"
#include "IC_TI.h"

#include "utils.h"

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl << endl;

    cout << "FIT for 0.5% in 6 years " << utils::FailureRate2FIT(0.5/100., 6*365*24.) << endl;

    component::setAmbientTemperature(45);

    schematic* FPGA2 = new schematic("Example FPGA_kintex7");


    FPGA2 -> addComponent(new IC ("IC12", 11, 55));
    FPGA2 -> lastAddedComponent () -> setDeviceTemperature (60);
    
    FPGA2 -> addComponent(new capacitor_WUERTH ("C241", "WCAP-CSGP", 1*capacitor ::uF, 2.5, 16));
    
    FPGA2 -> addComponent(new resistor_VISHAY_CRCWe3 ("R60", 4.7*resistor::kOhm, 0.002, 0.063));

//    example -> addComponent(new IC_TI("U101", "DS15EA101SQ/NOPB"));                             // Fetch the data from TI
//    example -> addComponent(new IC_TI("U102", "DS15BA101SQ/NOPB"));                             // Fetch the data from TI
    schematic* VCCO2V5 = new schematic("VCCO2V5");
    VCCO2V5 -> addComponent (new IC_TI ("RG1", "LMZ21701SILT"));

    schematic* GCU = new schematic("GCU_total");
    GCU -> addComponent(FPGA2);
    GCU -> addComponent(VCCO2V5);
    
    GCU -> setVerboseOutput(true);  // enable verbose output
    FPGA2 -> setVerboseOutput(true);
	GCU -> getFIT();

    return 0;
}
