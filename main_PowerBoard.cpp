#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor_WUERTH.h"
#include "resistor_VISHAY_CRCWe3.h"
#include "IC_TI.h"
#include "inductor_WUERTH.h"
#include "diode.h"

#include <cmath>


int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl;

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;

    /// JUNO Clock Receiver
    schematic* CLKreceiver = new schematic("JUNO Clock Receiver");

    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30EA101SQ/NOPB&CPN=&partNumber=DS30EA101#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30EA101SQE/NOPB&CPN=&partNumber=DS30EA101#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30EA101SQX/NOPB&CPN=&partNumber=DS30EA101#resultstable
    CLKreceiver -> addComponent(new IC_TI("U200", "DS15EA101SQ/NOPB"));

// input C
    CLKreceiver -> addComponent(new capacitor_WUERTH("C200", "WCAP-CSGP", 1*capacitor::uF, 24, 50));
    CLKreceiver -> addComponent(new capacitor_WUERTH("C203", "WCAP-CSGP", 1*capacitor::uF, 24, 50));
// second stage input C
    CLKreceiver -> addComponent(new capacitor_WUERTH("C201", "WCAP-CSGP", 1*capacitor::uF, 1.5, 10));	// check voltage
    CLKreceiver -> addComponent(new capacitor_WUERTH("C204", "WCAP-CSGP", 1*capacitor::uF, 1.5, 10));
// output Cs
    CLKreceiver -> addComponent(new capacitor_WUERTH("C202", "WCAP-CSGP", 1*capacitor::uF, 1.5, 10));
    CLKreceiver -> addComponent(new capacitor_WUERTH("C205", "WCAP-CSGP", 1*capacitor::uF, 1.5, 10));
// internal capacitor (CAP+ CAP-)
    CLKreceiver -> addComponent(new capacitor_WUERTH("C206", "WCAP-CSGP", 1*capacitor::uF, 1, 10));	// check voltage in datasheet
// bypass Cs (all at 3V3) 100n / 100p
    CLKreceiver -> addComponent(new capacitor_WUERTH("C209", "WCAP-CSGP", .1*capacitor::uF, 3.3, 16));
    CLKreceiver -> addComponent(new capacitor_WUERTH("C210", "WCAP-CSGP", .1*capacitor::uF, 3.3, 16));
    CLKreceiver -> addComponent(new capacitor_WUERTH("C211", "WCAP-CSGP", .1*capacitor::nF, 3.3, 10));
    CLKreceiver -> addComponent(new capacitor_WUERTH("C212", "WCAP-CSGP", .1*capacitor::nF, 3.3, 10));

    CLKreceiver -> addComponent(new resistor_VISHAY_CRCWe3("R201", 10*resistor::kOhm, 0.06, 0.1));	// calculate stress
    CLKreceiver -> addComponent(new resistor_VISHAY_CRCWe3("R203", 10*resistor::kOhm, 0.06, 0.1));
//FIXME diode U201 missing TPD2EUSB30DRTR

// power splitting etc.
    schematic* CLKPowerSplitting = new schematic("CLK decoupling");
// bypass Cs at 24V
    CLKPowerSplitting -> addComponent(new capacitor_WUERTH("C207", "WCAP-CSGP", .1*capacitor::uF, 24, 50));
    CLKPowerSplitting -> addComponent(new capacitor_WUERTH("C208", "WCAP-CSGP", .1*capacitor::uF, 24, 50));

    CLKPowerSplitting -> addComponent(new inductor_WUERTH("L200", "WE-CBF"));
    CLKPowerSplitting -> addComponent(new inductor_WUERTH("L201", "WE-CBF"));
    CLKPowerSplitting -> addComponent(new inductor_WUERTH("L202", "WE-SL5"));
// diodes missing
//FIXME diodes needed?

/****************************************************************************************************************/
    // JUNO Trigger Driver
    schematic* TriggerDriver = new schematic("JUNO Trigger Driver");

    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30BA101SQ/NOPB&CPN=&partNumber=DS30BA101#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30BA101SQE/NOPB&CPN=&partNumber=DS30BA101#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30BA101SQX/NOPB&CPN=&partNumber=DS30BA101#resultstable
    TriggerDriver -> addComponent(new IC_TI("U100", "DS15BA101SD/NOPB"));

// input Cs
    TriggerDriver -> addComponent(new capacitor_WUERTH("C103", "WCAP-CSGP", 1*capacitor::uF, 1.5, 10));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C105", "WCAP-CSGP", 1*capacitor::uF, 1.5, 10));
// output Cs
    TriggerDriver -> addComponent(new capacitor_WUERTH("C104", "WCAP-CSGP", 1*capacitor::uF, 2, 50));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C106", "WCAP-CSGP", 1*capacitor::uF, 2, 50));
// 100n bypass Cs
    TriggerDriver -> addComponent(new capacitor_WUERTH("C100", "WCAP-CSGP", 1*capacitor::uF, 3.3, 16));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C101", "WCAP-CSGP", 1*capacitor::uF, 3.3, 16));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C102", "WCAP-CSGP", 1*capacitor::uF, 3.3, 16));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C107", "WCAP-CSGP", 1*capacitor::uF, 3.3, 16));

    TriggerDriver -> addComponent(new resistor_VISHAY_CRCWe3("R104", 100*resistor::Ohm, 0.02, 0.1));
    TriggerDriver -> addComponent(new resistor_VISHAY_CRCWe3("R100", 953*resistor::Ohm, 0.05, 0.1));	// calculate stress
    TriggerDriver -> addComponent(new resistor_VISHAY_CRCWe3("R101", 50*resistor::Ohm, 0.05, 0.1));	// calculate stress
    TriggerDriver -> addComponent(new resistor_VISHAY_CRCWe3("R102", 50*resistor::Ohm, 0.05, 0.1));	// calculate stress

    ///JUNO DC/DC internal voltage
    schematic* PowerBoard = new schematic("Power Board (total)");
 
//    CLKreceiver -> setVerboseOutput(true);
//    CLKPowerSplitting -> setVerboseOutput(true);
//    TriggerDriver -> setVerboseOutput(true);

    PowerBoard -> addComponent(CLKreceiver);
    PowerBoard -> addComponent(CLKPowerSplitting);
    PowerBoard -> addComponent(TriggerDriver);
    PowerBoard -> setVerboseOutput(true);

    cout << endl;

    double FITPowerBoard = PowerBoard -> getFIT();

    cout << endl;
    schematic::printPartCount();

    cout << "\nTotal FIT of the Power Board:\t" << FITPowerBoard << " / " << component::FITunit << endl;
    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;

//    cout << "Failures of the Power Board within 6 years: \t" << schematic::getFailureRate( 6 * component::YEAR, FITPowerBoard ) * 100. << " %" << endl;

    return 0;
}
