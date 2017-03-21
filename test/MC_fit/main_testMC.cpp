#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "component_FIT.h"
#include "capacitor.h"
#include "resistor.h"
#include "IC.h"
#include "inductor.h"
#include "diode.h"
#include "crystal.h"

#include "capacitor_WUERTH.h"
#include "inductor_WUERTH.h"
#include "IC_TI.h"
#include "IC_MAXIM.h"
#include "IC_AD.h"
#include "PCB.h"

#include "capacitor_WIMA.h"
#include "capacitor_WIMA_SMD_PPS.h"
#include "capacitor_VISHAY.h"

#include "crystal_EPSON.h"

#include "utils.h"

#include <cstdlib>
#include <time.h>
#include <fstream>

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl << endl;

    cout << "FIT for 0.5% in 6 years " << utils::FailureRate2FIT(0.5/100., 6*365*24.) << endl;
    cout << endl << endl;

    component::setAmbientTemperature(40);

    schematic* example = new schematic("Example Board");
    example -> addComponent( new component_FIT("T1", 100), false);
    example -> getLastComponent() -> setProbSeriousError( 0.05 );
 
    example -> addComponent( new component_FIT("T2", 100), false);
    example -> getLastComponent() -> setProbSeriousError( 0.05 );

    example -> addComponent( new component_FIT("T3", 100), false);
    example -> getLastComponent() -> setProbSeriousError( 0.05 );

    example -> addComponent( new component_FIT("T4", 100), false);
    example -> getLastComponent() -> setProbSeriousError( 0.05 );

    double FITall, FITfmd;
    example -> MCcalculateFIT(FITall, FITfmd);

    example -> setVerboseOutput(true);
    float FIT = example -> getFIT();

    printf("%lf - %lf - %lf\n", FITall, FITfmd, FIT);

    return 0;
}
