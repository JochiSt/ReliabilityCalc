#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor.h"
#include "resistor.h"
#include "IC.h"
#include "inductor.h"
#include "diode.h"
#include "crystal.h"

#include "capacitor_WUERTH.h"
#include "inductor_WUERTH.h"
#include "IC_TI.h"
#include "PCB.h"

#include "capacitor_WIMA.h"
#include "capacitor_WIMA_SMD_PPS.h"
#include "capacitor_VISHAY.h"

#include "crystal_EPSON.h"

#include "utils.h"

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl << endl;

    cout << "FIT for 0.5% in 6 years " << utils::FailureRate2FIT(0.5/100., 6*365*24.) << endl;

    component::setAmbientTemperature(40);

    schematic* example = new schematic("Example Board");

    example -> addComponent(new capacitor_WUERTH("C1", "WCAP-CSGP",  1*capacitor::uF,  1, 50)); // lowest stress
    example -> addComponent(new capacitor_WUERTH("C2", "WCAP-CSGP",  1*capacitor::uF, 14, 50));
    example -> addComponent(new capacitor_WUERTH("C2a", "WCAP-CSGP",  1*capacitor::uF, 14, 50), 10);
    example -> addComponent(new capacitor_WUERTH("C3", "WCAP-CSGP",  1*capacitor::uF, 24, 50));
    example -> addComponent(new capacitor_WUERTH("C4", "WCAP-CSGP",  1*capacitor::uF, 34, 50));
    example -> addComponent(new capacitor_WUERTH("C5", "WCAP-CSGP",  1*capacitor::uF, 50, 50)); // maximal stress

    example -> addComponent(new capacitor_VISHAY("C90", capacitor_VISHAY::CLASS_1, 1*capacitor::pF, 24, 50));
    example -> addComponent(new capacitor_VISHAY("C91", capacitor_VISHAY::CLASS_2, 1*capacitor::pF, 24, 50));

    example -> addComponent(new capacitor_WIMA("C10", 1*capacitor::uF, 24, 50));
    example -> addComponent(new capacitor_WIMA_SMD_PPS("C10", 1*capacitor::uF, 24, 50));

    example -> addComponent(new inductor_WUERTH("L1", "WE-PoE+"));

    example -> addComponent(new crystal("Q1", 36, 25));
    example -> addComponent(new crystal_EPSON("Q1", 36, 25));

    example -> addComponent(new IC_TI("GCU_ISO", "ISO7341CQDWQ1"));
    example -> lastAddedComponent() -> setDeviceTemperature(55);

    example -> addComponent(new PCB("PCB", 4 ,1000, PCB::MICRO_VIA , 500)); 

    example -> setVerboseOutput(true);  // enable verbose output
    example -> getFIT();

    schematic::printPartCount();

    return 0;
}
