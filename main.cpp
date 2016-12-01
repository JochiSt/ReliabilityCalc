#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor.h"
#include "resistor.h"
#include "IC.h"
#include "inductor.h"
#include "diode.h"

#include "capacitor_WUERTH.h"
#include "inductor_WUERTH.h"
#include "IC_TI.h"

#include <cmath>

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl << endl;

    component::setAmbientTemperature(45);

    schematic* example = new schematic("JUNO Example Board");

    example -> addComponent(new capacitor_WUERTH("C1", "WCAP-CSGP",  1*capacitor::uF,  1, 50));
    example -> addComponent(new capacitor_WUERTH("C2", "WCAP-CSGP",  1*capacitor::uF, 14, 50));
    example -> addComponent(new capacitor_WUERTH("C3", "WCAP-CSGP",  1*capacitor::uF, 24, 50));
    example -> addComponent(new capacitor_WUERTH("C4", "WCAP-CSGP",  1*capacitor::uF, 34, 50));
    example -> addComponent(new capacitor_WUERTH("C5", "WCAP-CSGP",  1*capacitor::uF, 50, 50));
    example -> addComponent(new capacitor_WUERTH("C6", "WCAP-CSGP",  1*capacitor::uF, 55, 50));

    example -> addComponent(new inductor_WUERTH("L1", "WE-PoE+"));

    example -> addComponent(new IC_TI("U101", "DS30EA101SQ/NOPB"));

    example -> setVerboseOutput(true);  // enable verbose output
	example -> getFIT();

    return 0;
}
