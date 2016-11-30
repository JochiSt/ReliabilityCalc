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

#include <cmath>

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl << endl;

    component::setAmbientTemperature(40);

    schematic* example = new schematic("JUNO Example Board");

    example -> addComponent(new capacitor_WUERTH("C1", "WCAP-CSGP",  1*capacitor::uF,  1, 50));
    example -> addComponent(new capacitor_WUERTH("C2", "WCAP-CSGP",  1*capacitor::uF, 14, 50));
    example -> addComponent(new capacitor_WUERTH("C3", "WCAP-CSGP",  1*capacitor::uF, 24, 50));
    example -> addComponent(new capacitor_WUERTH("C4", "WCAP-CSGP",  1*capacitor::uF, 34, 50));
    example -> addComponent(new capacitor_WUERTH("C5", "WCAP-CSGP",  1*capacitor::uF, 50, 50));
    example -> addComponent(new capacitor_WUERTH("C6", "WCAP-CSGP",  1*capacitor::uF, 55, 50));

    example -> setVerboseOutput(true);  // enable verbose output
	example -> getFIT();

    return 0;
}
