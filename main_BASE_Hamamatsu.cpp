#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor.h"
#include "resistor.h"
#include "IC.h"
#include "inductor.h"
#include "diode.h"

#include "resistor_VISHAY_CRCWe3.h"

#include "inductor_WUERTH.h"

#include "IC_TI.h"
#include "PCB.h"

#include "capacitor_WIMA.h"
#include "capacitor_WIMA_SMD_PPS.h"
#include "capacitor_VISHAY.h"
#include "capacitor_WUERTH.h"

#include "utils.h"

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl << endl;

    component::setAmbientTemperature(40);

    // maximal voltage 3kV
    // total resistance ~ 9.92 MOhm
    float BaseCurrent = 3000. / 9.02E6; 
    float BaseCurrent2 = BaseCurrent * BaseCurrent;

    schematic* voltage_divider = new schematic("Voltage Divider");

    // Resistors for base voltage divider VISHAY CRCWe3 in SMD 2010 (5025 Metric) Pmax = 0.75 W Umax = 400V
    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R1a", 560*resistor::kOhm, 560e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R1b", 560*resistor::kOhm, 560e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R1c", 560*resistor::kOhm, 560e3*BaseCurrent2, 0.75));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R2a", 560*resistor::kOhm, 560e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R2b", 560*resistor::kOhm, 560e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R2c", 560*resistor::kOhm, 560e3*BaseCurrent2, 0.75));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R3", 180*resistor::kOhm, 180e3*BaseCurrent2, 0.75));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R4a", 560*resistor::kOhm, 560e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R4b", 470*resistor::kOhm, 470e3*BaseCurrent2, 0.75));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R5a", 560*resistor::kOhm, 560e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R5b", 560*resistor::kOhm, 560e3*BaseCurrent2, 0.75));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R6a", 430*resistor::kOhm, 430e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R6b", 470*resistor::kOhm, 470e3*BaseCurrent2, 0.75));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R7", 620*resistor::kOhm, 620e3*BaseCurrent2, 0.75));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R8", 300*resistor::kOhm, 300e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R9", 300*resistor::kOhm, 300e3*BaseCurrent2, 0.75));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R10", 300*resistor::kOhm, 300e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new capacitor_WIMA_SMD_PPS("C1", 10*capacitor::nF, 300e3*BaseCurrent, 630));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R11", 300*resistor::kOhm, 300e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new capacitor_WIMA_SMD_PPS("C2", 10*capacitor::nF, 300e3*BaseCurrent, 630));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R12", 300*resistor::kOhm, 300e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new capacitor_WIMA_SMD_PPS("C3", 10*capacitor::nF, 300e3*BaseCurrent, 630));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R13", 300*resistor::kOhm, 300e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new capacitor_WIMA_SMD_PPS("C4", 10*capacitor::nF, 300e3*BaseCurrent, 630));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R1", 100*resistor::Ohm, 0.1, 0.25));	// 1210
    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R2", 100*resistor::Ohm, 0.1, 0.25));
    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R3", 100*resistor::Ohm, 0.1, 0.25));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R16", 10*resistor::kOhm, 10e3*BaseCurrent2, 0.75));	// FIXME right stress
    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R3", 100*resistor::Ohm, 0.1, 0.25));

    voltage_divider -> addComponent(new resistor_VISHAY_CRCWe3("R19", 10*resistor::kOhm, 10e3*BaseCurrent2, 0.75));
    voltage_divider -> addComponent(new capacitor_VISHAY("C5", capacitor_VISHAY::CLASS_2, 4.7*capacitor::nF, 3000, 6000));

    schematic* adc_input_protection = new schematic("ADC protection");
    adc_input_protection -> addComponent(new capacitor_VISHAY("C6", capacitor_VISHAY::CLASS_2, 47*capacitor::nF, 3000, 6000));
    adc_input_protection -> addComponent(new resistor_VISHAY_CRCWe3("R17", 10*resistor::kOhm, 0.09, 0.1));	// FIXME add right stress
    adc_input_protection -> addComponent(new resistor_VISHAY_CRCWe3("R16", 10*resistor::kOhm, 0.09, 0.1));	// FIXME add right stress

    adc_input_protection -> addComponent(new resistor_VISHAY_CRCWe3("R15", 51*resistor::Ohm, 0.09, 0.1));	// FIXME add right stress
    adc_input_protection -> addComponent(new resistor_VISHAY_CRCWe3("R14", 51*resistor::Ohm, 0.09, 0.1));	// FIXME add right stress
    adc_input_protection -> addComponent(new resistor_VISHAY_CRCWe3("R13", 100*resistor::Ohm, 0.09, 0.1));	// FIXME add right stress

    // TODO add Gas Discharge Tubes and TVS Diode(s)
    
    adc_input_protection -> addComponent(new resistor_VISHAY_CRCWe3("R6",  100*resistor::kOhm, 0.09, 0.1));	// FIXME add right stress
    adc_input_protection -> addComponent(new resistor_VISHAY_CRCWe3("R18", 100*resistor::kOhm, 0.09, 0.1));	// FIXME add right stress

    adc_input_protection -> addComponent(new capacitor_WUERTH("C7", "WCAP-CSGP",  1*capacitor::uF, 12, 25));
    adc_input_protection -> addComponent(new capacitor_WUERTH("C8", "WCAP-CSGP",  1*capacitor::uF, 12, 25));

//    adc_input_protection -> setVerboseOutput(true);

    schematic* base_hamamatsu = new schematic("Base Hamamatsu");
    base_hamamatsu -> addComponent(voltage_divider);
    base_hamamatsu -> addComponent(adc_input_protection);
    base_hamamatsu -> addComponent(new PCB("PCB", 2 ,1000, PCB::THROUGH_HOLE, 500)); 

    base_hamamatsu -> setVerboseOutput(true);  // enable verbose output
    base_hamamatsu -> getFIT();

    schematic::printPartCount();

    return 0;
}
