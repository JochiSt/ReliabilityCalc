#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor_WUERTH.h"
#include "resistor_VISHAY_CRCWe3.h"
#include "IC.h"
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
    schematic* CLKrecevier = new schematic("JUNO Clock Receiver");

    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30EA101SQ/NOPB&CPN=&partNumber=DS30EA101#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30EA101SQE/NOPB&CPN=&partNumber=DS30EA101#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30EA101SQX/NOPB&CPN=&partNumber=DS30EA101#resultstable
    CLKrecevier -> addComponent(new IC("DS30EA101", 330, IC::DPPM, 3.23e8, 55, IC::MTTF));

    CLKrecevier -> addComponent(new capacitor_WUERTH("C200", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    CLKrecevier -> addComponent(new capacitor_WUERTH("C201", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    CLKrecevier -> addComponent(new capacitor_WUERTH("C202", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    CLKrecevier -> addComponent(new capacitor_WUERTH("C203", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    CLKrecevier -> addComponent(new capacitor_WUERTH("C204", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    CLKrecevier -> addComponent(new capacitor_WUERTH("C205", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    CLKrecevier -> addComponent(new capacitor_WUERTH("C206", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    CLKrecevier -> addComponent(new capacitor_WUERTH("C207", "WCAP-CSGP", 1*capacitor::uF, 10, 50));

    CLKrecevier -> addComponent(new resistor_VISHAY_CRCWe3("R200", 1*resistor::MOhm, 0.2, 0.1));
    CLKrecevier -> addComponent(new resistor_VISHAY_CRCWe3("R201", 1*resistor::MOhm, 0.2, 0.1));
    CLKrecevier -> addComponent(new resistor_VISHAY_CRCWe3("R202", 1*resistor::MOhm, 0.2, 0.1));

    /// JUNO Clock Power Splitting

    schematic* CLKPowerSplitting = new schematic("Clock Power Splitting");

    CLKPowerSplitting -> addComponent(new inductor_WUERTH("L100", "WE"));
    CLKPowerSplitting -> addComponent(new inductor_WUERTH("L101", "WE"));

    ///JUNO Trigger Driver

    schematic* TriggerDriver = new schematic("JUNO Trigger Driver");

    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30BA101SQ/NOPB&CPN=&partNumber=DS30BA101#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30BA101SQE/NOPB&CPN=&partNumber=DS30BA101#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30BA101SQX/NOPB&CPN=&partNumber=DS30BA101#resultstable
    TriggerDriver -> addComponent(new IC("DS30BA101", 182, IC::DPPM, 1.552e8, 55,IC::MTTF));

    TriggerDriver -> addComponent(new capacitor_WUERTH("C300", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C301", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C302", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C303", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C304", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C305", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C306", "WCAP-CSGP", 1*capacitor::uF, 10, 50));

    TriggerDriver -> addComponent(new resistor_VISHAY_CRCWe3("R300", 1*resistor::MOhm, 0.2, 0.1));
    TriggerDriver -> addComponent(new resistor_VISHAY_CRCWe3("R301", 1*resistor::MOhm, 0.2, 0.1));
    TriggerDriver -> addComponent(new resistor_VISHAY_CRCWe3("R302", 1*resistor::MOhm, 0.2, 0.1));
    TriggerDriver -> addComponent(new resistor_VISHAY_CRCWe3("R303", 1*resistor::MOhm, 0.2, 0.1));

    ///JUNO DC/DC internal voltage

    schematic* DCDCinternal = new schematic("JUNO DC/DC internal voltage");

    // http://cds.linear.com/docs/en/datasheet/8614fb.pdf
    // TODO: find ELFR value
    DCDCinternal -> addComponent(new IC("LT8614", 0, IC::DPPM, 6.498e8, 55,IC::MTTF));

    DCDCinternal -> addComponent(new capacitor_WUERTH("C900", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDCinternal -> addComponent(new capacitor_WUERTH("C901", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDCinternal -> addComponent(new capacitor_WUERTH("C902", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDCinternal -> addComponent(new capacitor_WUERTH("C903", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDCinternal -> addComponent(new capacitor_WUERTH("C904", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDCinternal -> addComponent(new capacitor_WUERTH("C905", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDCinternal -> addComponent(new capacitor_WUERTH("C906", "WCAP-CSGP", 1*capacitor::uF, 10, 50));

    DCDCinternal -> addComponent(new resistor_VISHAY_CRCWe3("R900", 1*resistor::MOhm, 0.2, 0.1));
    DCDCinternal -> addComponent(new resistor_VISHAY_CRCWe3("R901", 1*resistor::MOhm, 0.2, 0.1));
    DCDCinternal -> addComponent(new resistor_VISHAY_CRCWe3("R902", 1*resistor::MOhm, 0.2, 0.1));

    DCDCinternal -> addComponent(new inductor_WUERTH("L900", "WE"));

    ///DCDC 1.8V for Analog Part

    schematic* DCDC18 = new schematic("JUNO 1.8 DC/DC for Analog Part");

    // http://www.ti.com/quality/docs/estimator.tsp?OPN=LM3673TL-1.2/NOPB&CPN=&partNumber=LM3673TL#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=LM3673TL-1.5/NOPB&CPN=&partNumber=LM3673TL#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=LM3673TL-1.8/NOPB&CPN=&partNumber=LM3673TL#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=LM3673TL-ADJ/NOPB&CPN=&partNumber=LM3673TL#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=LM3673TLX-1.2/NOPB&CPN=&partNumber=LM3673TL#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=LM3673TLX-1.5/NOPB&CPN=&partNumber=LM3673TL#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=LM3673TLX-1.8/NOPB&CPN=&partNumber=LM3673TL#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=LM3673TLX-ADJ/NOPB&CPN=&partNumber=LM3673TL#resultstable
    DCDC18 -> addComponent(new IC("LM3673TL", 41, IC::DPPM, 1.42e8, 55, IC::MTTF));

    DCDC18 -> addComponent(new capacitor_WUERTH("C500", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC18 -> addComponent(new capacitor_WUERTH("C501", "WCAP-CSGP", 1*capacitor::uF, 10, 50));

    DCDC18 -> addComponent(new inductor_WUERTH("L500", "WE-"));

    ///DCDC 3.3V for Analog Part

    schematic* DCDC33A = new schematic("JUNO DC/DC 3.3V for Analog Part");

    // http://www.ti.com/quality/docs/estimator.tsp?OPN=TPS5432DDA&CPN=&partNumber=TPS5432DDA#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=TPS5432DDAR&CPN=&partNumber=TPS5432DDA#resultstable
    DCDC33A -> addComponent(new IC("TPS5432DDA", 18, IC::DPPM, 1e10, 55, IC::MTTF));

    DCDC33A -> addComponent(new capacitor_WUERTH("C600", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC33A -> addComponent(new capacitor_WUERTH("C601", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC33A -> addComponent(new capacitor_WUERTH("C602", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC33A -> addComponent(new capacitor_WUERTH("C603", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC33A -> addComponent(new capacitor_WUERTH("C604", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC33A -> addComponent(new capacitor_WUERTH("C605", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC33A -> addComponent(new capacitor_WUERTH("C606", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC33A -> addComponent(new capacitor_WUERTH("C607", "WCAP-CSGP", 1*capacitor::uF, 10, 50));

    DCDC33A -> addComponent(new resistor_VISHAY_CRCWe3("R600", 1*resistor::MOhm, 0.2, 0.1));
    DCDC33A -> addComponent(new resistor_VISHAY_CRCWe3("R601", 1*resistor::MOhm, 0.2, 0.1));
    DCDC33A -> addComponent(new resistor_VISHAY_CRCWe3("R602", 1*resistor::MOhm, 0.2, 0.1));
    DCDC33A -> addComponent(new resistor_VISHAY_CRCWe3("R603", 1*resistor::MOhm, 0.2, 0.1));
    DCDC33A -> addComponent(new resistor_VISHAY_CRCWe3("R604", 1*resistor::MOhm, 0.2, 0.1));

    DCDC33A -> addComponent(new inductor_WUERTH("L600", "WE-"));

    /// JUNO 3V3 DC/DC for cable handling

    schematic* DCDC33C = new schematic("JUNO DC/DC 3.3V for cable handling");

    DCDC33C -> addComponent(new IC("LM3673TL", 41, IC::DPPM, 1.42e8, 55, IC::MTTF));

    DCDC33C -> addComponent(new capacitor_WUERTH("C800", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC33C -> addComponent(new capacitor_WUERTH("C801", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC33C -> addComponent(new capacitor_WUERTH("C802", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC33C -> addComponent(new capacitor_WUERTH("C803", "WCAP-CSGP", 1*capacitor::uF, 10, 50));

    DCDC33C -> addComponent(new resistor_VISHAY_CRCWe3("R800", 1*resistor::MOhm, 0.2, 0.1));
    DCDC33C -> addComponent(new resistor_VISHAY_CRCWe3("R801", 1*resistor::MOhm, 0.2, 0.1));

    DCDC33C -> addComponent(new inductor_WUERTH("L800", "WE-"));

    /// JUNO 2V5 DC/DC for cable handling

    schematic* DCDC25C = new schematic("JUNO DC/DC 1.8V for cable handling");

    DCDC25C -> addComponent(new IC("LM3673TL", 41, IC::DPPM, 1.42e8, 55, IC::MTTF));

    DCDC25C -> addComponent(new capacitor_WUERTH("C700", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC25C -> addComponent(new capacitor_WUERTH("C701", "WCAP-CSGP", 1*capacitor::uF, 10, 50));
    DCDC25C -> addComponent(new capacitor_WUERTH("C702", "WCAP-CSGP", 1*capacitor::uF, 10, 50));

    DCDC25C -> addComponent(new resistor_VISHAY_CRCWe3("R700", 1*resistor::MOhm, 0.2, 0.1));
    DCDC25C -> addComponent(new resistor_VISHAY_CRCWe3("R701", 1*resistor::MOhm, 0.2, 0.1));

    DCDC25C -> addComponent(new inductor_WUERTH("L701",125, Iqual)); // ??


    /// POE DCDC 24V -> 12V

    schematic* DCDCPOE = new schematic("POE DCDC Converter");

    // http://www.ti.com/quality/docs/estimator.tsp?OPN=LMR24220TL/NOPB&CPN=&partNumber=LMR24220#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=LMR24220TLX/NOPB&CPN=&partNumber=LMR24220#resultstable
    DCDCPOE -> addComponent(new IC("LMR24220", 19, IC::DPPM, 5.54e8, 55 , IC::MTTF));

    DCDCPOE -> addComponent(new capacitor_WUERTH("C1000", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    DCDCPOE -> addComponent(new capacitor_WUERTH("C1001",0.1, 40, 0.16, 120, capacitor_WUERTH::FITe9));
    DCDCPOE -> addComponent(new capacitor_WUERTH("C1002",0.1, 40, 0.16, 120, capacitor_WUERTH::FITe9));
    DCDCPOE -> addComponent(new capacitor_WUERTH("C1003",0.1, 40, 0.16, 120, capacitor_WUERTH::FITe9));
    DCDCPOE -> addComponent(new capacitor_WUERTH("C1004",0.1, 40, 0.16, 120, capacitor_WUERTH::FITe9));
    DCDCPOE -> addComponent(new capacitor_WUERTH("C1005", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    DCDCPOE -> addComponent(new capacitor_WUERTH("C1006", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    DCDCPOE -> addComponent(new capacitor_WUERTH("C1007", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    DCDCPOE -> addComponent(new capacitor_WUERTH("C1008", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));

    DCDCPOE -> addComponent(new resistor_VISHAY_CRCWe3("R1001", 1*resistor::MOhm, 0.2, 0.1));
    DCDCPOE -> addComponent(new resistor_VISHAY_CRCWe3("R1000", 1*resistor::MOhm, 0.2, 0.1));
    DCDCPOE -> addComponent(new resistor_VISHAY_CRCWe3("R1002", 1*resistor::MOhm, 0.2, 0.1));
    DCDCPOE -> addComponent(new resistor_VISHAY_CRCWe3("R1003", 1*resistor::MOhm, 0.2, 0.1));


    DCDCPOE -> addComponent(new inductor_WUERTH("L1000",1.3,inductor_WUERTH::FITe9));



    cout << "###############################################################################" << endl;
    cout << endl;

    ///Combine everything - Power board

    schematic* PowerBoard = new schematic("Power Board");

    PowerBoard -> addComponent(new inductor_WUERTH("L1","WE-"));
    PowerBoard -> addComponent(new inductor_WUERTH("L2","WE-"));
    PowerBoard -> addComponent(new inductor_WUERTH("L3","WE-"));
    PowerBoard -> addComponent(new inductor_WUERTH("L4","WE-"));
    PowerBoard -> addComponent(new inductor_WUERTH("L5","WE-"));
    PowerBoard -> addComponent(new inductor_WUERTH("L6","WE-"));
    PowerBoard -> addComponent(new inductor_WUERTH("L7","WE-"));

    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R1", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R2", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));

    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R3", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R4", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R5", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R6", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R7", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R8", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R9", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R10", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R11", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R12", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R13", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R14", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R15", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R16", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));
    PowerBoard -> addComponent(new resistor_VISHAY_CRCWe3("R17", 0.1, 40, resistor_VISHAY_CRCWe3::FITe9 ));

    PowerBoard -> addComponent(new capacitor_WUERTH("C1", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C2", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C3", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C4", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C5", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C6", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C7", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C8", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C9", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C10", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C11", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C12", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C13", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));
    PowerBoard -> addComponent(new capacitor_WUERTH("C14", 0.04, 40, 0.07, 120, capacitor_WUERTH::FITe9));

    PowerBoard -> addComponent(CLKrecevier);
    PowerBoard -> addComponent(CLKPowerSplitting);
    PowerBoard -> addComponent(TriggerDriver);
    PowerBoard -> addComponent(DCDCinternal);
    PowerBoard -> addComponent(DCDC18);
    PowerBoard -> addComponent(DCDC33A);
    PowerBoard -> addComponent(DCDC33C);
    PowerBoard -> addComponent(DCDC25C);
    PowerBoard -> addComponent(DCDCPOE);

    component::environment = component::GF;
    component::calculation_method = component::MIL_HDBK_217F_NOTICE2;

    /*double FITCLKrecevier = CLKrecevier -> getFIT();
    double FITCLKPowerSplitting = CLKPowerSplitting -> getFIT();
    double FITTriggerDriver = TriggerDriver -> getFIT();
    double FITDCDCInternal = DCDCinternal -> getFIT();
    double FITDCDC18 = DCDC18 -> getFIT();
    double FITDCDC33A = DCDC33A -> getFIT();
    double FITDCDC33C = DCDC33C -> getFIT();
    double FITDCDC18C = DCDC18C -> getFIT();*/
    double FITPowerBoard = PowerBoard -> getFIT(true);
    schematic::printPartCount();

    cout << "\nTotal FIT of the Power Board:\t" << FITPowerBoard << " / " << component::FITunit << endl;
    cout << "\nTotal FIT of the Power Board:\t" << FITPowerBoard*1000. << " / 1E9h " << endl;

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;

    cout << "Failures of the Power Board within 6 years: \t" << schematic::getFailureRate( 6 * component::YEAR, FITPowerBoard ) * 100. << " %" << endl;

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;
    cout << "EARLY FAILURES" << endl;
    cout << endl;

    float weibullExponentMean = PowerBoard->estimateWeibullExponent(3000, schematic::MEAN);
    float weibullExponentError = PowerBoard->estimateWeibullExponent(3000, schematic::STDDEV);

    cout << endl;
    cout << "Weibull exponent determined from ICs:\t\t " << weibullExponentMean << " +/- " << weibullExponentError << std::endl;

    float earlyFailureRate = schematic::getFailureRate(3000., FITPowerBoard, weibullExponentMean);
    float earlyFailureRateError = schematic::getFailureRateError(3000., FITPowerBoard, weibullExponentMean, weibullExponentError);
    cout << "Early failures of the Power Board within 3000h:\t(" << earlyFailureRate*100. << " +/- " << earlyFailureRateError*100. << ") %" << endl;

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;

    //float testT = 125;
    //cout << "Acceleration Factor for "<< testT << " degC: " << PowerBoard -> getAccelerationFactor(testT, 40) << endl;
    //cout << "\nTotal FIT of the Power Board:\t" << FITPowerBoard*1000 << " / " << "10^9h" << endl;

//######################################################################################################################

    //CLKdecoupling -> exportToFile("test");      // save schematic in 'test'
    //CLKdecoupling -> clear();                   // clear all parts
    //CLKdecoupling -> importFromFile("test");    // re-import from 'test'
    //CLKdecoupling -> exportToFile("test2");     // export to 'test2' -> at the end 'test' and 'test2' should be the same

    return 0;
}
