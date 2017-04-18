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

#include "resistor_VISHAY_CRCWe3.h"
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

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl << endl;

    cout << "FIT for C_STRESS% in 6 years " << utils::FailureRate2FIT(0.5/100., 6*365*24.) << endl;

    component::setAmbientTemperature(40);

    const float C_STRESS = 0.49;
    const float R_STRESS = 0.49;

    schematic* TsinghuaFMC = new schematic("Tsinghua FMC");

    TsinghuaFMC -> addComponent(new IC_AD("U16", "AD5064"));
    TsinghuaFMC -> addComponent(new IC_AD("U14", "AD8057"));
    TsinghuaFMC -> addComponent(new IC_AD("U15", "AD8057"));
    TsinghuaFMC -> addComponent(new IC_AD("U17", "AD824"));
    TsinghuaFMC -> addComponent(new IC_AD("U9", "ADA4932-2"));
//    TsinghuaFMC -> addComponent(new IC_AD("U18", "ADG902"));
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 10 * capacitor::nF, C_STRESS), 52);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 100 * capacitor::nF, C_STRESS), 20);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 100 * capacitor::pF, C_STRESS), 12);

    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 10 * capacitor::uF, C_STRESS), 2);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 10 * capacitor::pF, C_STRESS), 2);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 1 * capacitor::uF, C_STRESS), 5);

    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 10 * capacitor::uF, C_STRESS), 2);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 20 * capacitor::pF, C_STRESS), 4);

    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 22 * capacitor::uF, C_STRESS), 2);

    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C161","WCAP-CSGP", 3.3 * capacitor::nF, C_STRESS));
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C143","WCAP-CSGP", 3.9 * capacitor::nF, C_STRESS));
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C144","WCAP-CSGP", 39 * capacitor::pF, C_STRESS));
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C145","WCAP-CSGP", 4.7 * capacitor::pF, C_STRESS));
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 10 * capacitor::nF, C_STRESS), 2);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C116","WCAP-CSGP", 22 * capacitor::nF, C_STRESS));
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 100 * capacitor::nF, C_STRESS), 48);


    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C117","WCAP-CSGP", 470 * capacitor::nF, C_STRESS));
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C148","WCAP-CSGP", 100 * capacitor::pF, C_STRESS));
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 10 * capacitor::uF, C_STRESS),8);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C198","WCAP-CSGP", 10 * capacitor::pF, C_STRESS));
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 1 * capacitor::uF, C_STRESS),4);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 1 * capacitor::uF, C_STRESS),8);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 10 * capacitor::uF, C_STRESS),12);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 1 * capacitor::uF, C_STRESS),3);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 100 * capacitor::uF, C_STRESS),4);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 10 * capacitor::uF, C_STRESS),8);
    TsinghuaFMC -> addComponent(new capacitor_WUERTH("C","WCAP-CSGP", 330 * capacitor::uF, C_STRESS),2);

    TsinghuaFMC -> addComponent(new IC_TI("U7", "LMX2581"));
    TsinghuaFMC -> addComponent(new IC_TI("U4", "LMZ12001"));

    TsinghuaFMC -> addComponent(new IC_AD("U2", "REF191"));
    TsinghuaFMC -> addComponent(new IC_AD("U1", "REF192"));
    TsinghuaFMC -> addComponent(new IC_AD("U20", "REF192"));

    TsinghuaFMC -> addComponent(new IC_TI("U2", "TPS7A7001"));

    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R84", 100*resistor::Ohm, R_STRESS));
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R85", 100*resistor::Ohm, R_STRESS));
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R78", 18*resistor::Ohm, R_STRESS));
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R65", 1*resistor::kOhm, R_STRESS));

    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R", 33*resistor::Ohm, R_STRESS),5);
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R66", 47*resistor::Ohm, R_STRESS));
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R", 50*resistor::Ohm, R_STRESS),6);
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R66", 47*resistor::Ohm, R_STRESS));
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R69", 50*resistor::Ohm, R_STRESS));
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R67", 50*resistor::Ohm, R_STRESS));
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R45", 50*resistor::Ohm, R_STRESS));
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R72", 50*resistor::Ohm, R_STRESS));
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R26", 50*resistor::Ohm, R_STRESS));

    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R", 10*resistor::kOhm, R_STRESS),6);
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R73", 50*resistor::Ohm, R_STRESS));
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R", 1*resistor::kOhm, R_STRESS),8);
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R46", 50*resistor::Ohm, R_STRESS));
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R", 1*resistor::kOhm, R_STRESS),2);
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R", 1*resistor::kOhm, R_STRESS),2);
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R", 1*resistor::kOhm, R_STRESS),2);
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R", 1*resistor::kOhm, R_STRESS),4);
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R", 1*resistor::kOhm, R_STRESS),2);
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R", 1*resistor::kOhm, R_STRESS),4);
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R71", 50*resistor::Ohm, R_STRESS));
    TsinghuaFMC -> addComponent(new resistor_VISHAY_CRCWe3("R5", 50*resistor::Ohm, R_STRESS));

    TsinghuaFMC -> addComponent(new PCB("PCB", 4 ,1000, PCB::MICRO_VIA , 500)); 

    TsinghuaFMC -> setVerboseOutput(true);  // enable verbose output
    TsinghuaFMC -> getFIT();

    schematic::printPartCount();

    return 0;
}
