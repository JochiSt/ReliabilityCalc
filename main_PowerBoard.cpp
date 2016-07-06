#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor.h"
#include "resistor.h"
#include "IC.h"
#include "inductor.h"
#include "diode.h"

#include <cmath>


int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl;

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;

    ///Resistor Quality
    resistor::Rquality_t Rqual = resistor::Q_S;

    ///Capacitor Quality
    capacitor::Cquality_t Cqual = capacitor::Q_S;

    ///Inductor Quality
    inductor::Iquality_t Iqual = inductor::Q_M;

    /// JUNO Clock Receiver

    schematic* CLKrecevier = new schematic("JUNO Clock Receiver");

    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30EA101SQ/NOPB&CPN=&partNumber=DS30EA101#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30EA101SQE/NOPB&CPN=&partNumber=DS30EA101#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30EA101SQX/NOPB&CPN=&partNumber=DS30EA101#resultstable
    CLKrecevier -> addComponent(new IC("DS30EA101", 330, IC::DPPM, 3.23e8, 55, IC::MTTF));

    CLKrecevier -> addComponent(new capacitor("C200", 0.1, 40, 0.16, 120, capacitor::FITe9));
    CLKrecevier -> addComponent(new capacitor("C201", 0.1, 40, 0.16, 120, capacitor::FITe9));
    CLKrecevier -> addComponent(new capacitor("C202", 0.04, 40, 0.07, 120, capacitor::FITe9));
    CLKrecevier -> addComponent(new capacitor("C203", 0.1, 40, 0.16, 120, capacitor::FITe9));
    CLKrecevier -> addComponent(new capacitor("C204",  0.04, 40, 0.07, 120, capacitor::FITe9));
    CLKrecevier -> addComponent(new capacitor("C205", 0.1, 40, 0.16, 120, capacitor::FITe9));
    CLKrecevier -> addComponent(new capacitor("C206",  0.04, 40, 0.07, 120, capacitor::FITe9));
    CLKrecevier -> addComponent(new capacitor("C207",  0.04, 40, 0.07, 120, capacitor::FITe9));

    CLKrecevier -> addComponent(new resistor("R200", 0.1, 40, resistor::FITe9 ));
    CLKrecevier -> addComponent(new resistor("R201", 0.1, 40, resistor::FITe9 ));
    CLKrecevier -> addComponent(new resistor("R202", 0.1, 40, resistor::FITe9 ));

    /// JUNO Clock Power Splitting

    schematic* CLKPowerSplitting = new schematic("Clock Power Splitting");

    CLKPowerSplitting -> addComponent(new inductor("L100", 0.13, inductor::FITe9));
    CLKPowerSplitting -> addComponent(new inductor("L101", 0.13, inductor::FITe9));

    ///JUNO Trigger Driver

    schematic* TriggerDriver = new schematic("JUNO Trigger Driver");

    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30BA101SQ/NOPB&CPN=&partNumber=DS30BA101#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30BA101SQE/NOPB&CPN=&partNumber=DS30BA101#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=DS30BA101SQX/NOPB&CPN=&partNumber=DS30BA101#resultstable
    TriggerDriver -> addComponent(new IC("DS30BA101", 182, IC::DPPM, 1.552e8, 55,IC::MTTF));

    TriggerDriver -> addComponent(new capacitor("C300",  0.04, 40, 0.07, 120, capacitor::FITe9));
    TriggerDriver -> addComponent(new capacitor("C301",  0.04, 40, 0.07, 120, capacitor::FITe9));
    TriggerDriver -> addComponent(new capacitor("C302",  0.04, 40, 0.07, 120, capacitor::FITe9));
    TriggerDriver -> addComponent(new capacitor("C303", 0.1, 40, 0.16, 120, capacitor::FITe9));
    TriggerDriver -> addComponent(new capacitor("C304", 0.1, 40, 0.16, 120, capacitor::FITe9));
    TriggerDriver -> addComponent(new capacitor("C305",  0.04, 40, 0.07, 120, capacitor::FITe9));
    TriggerDriver -> addComponent(new capacitor("C306",  0.04, 40, 0.07, 120, capacitor::FITe9));

    TriggerDriver -> addComponent(new resistor("R300", 0.1, 40, resistor::FITe9 ));
    TriggerDriver -> addComponent(new resistor("R301", 0.1, 40, resistor::FITe9 ));
    TriggerDriver -> addComponent(new resistor("R302", 0.1, 40, resistor::FITe9 ));
    TriggerDriver -> addComponent(new resistor("R303", 0.1, 40, resistor::FITe9 ));

    ///JUNO DC/DC internal voltage

    schematic* DCDCinternal = new schematic("JUNO DC/DC internal voltage");

    // http://cds.linear.com/docs/en/datasheet/8614fb.pdf
    // TODO: find ELFR value
    DCDCinternal -> addComponent(new IC("LT8614", 0, IC::DPPM, 6.498e8, 55,IC::MTTF));

    DCDCinternal -> addComponent(new capacitor("C900", 0.1, 40, 0.16, 120, capacitor::FITe9));
    DCDCinternal -> addComponent(new capacitor("C901", 0.1, 40, 0.16, 120, capacitor::FITe9));
    DCDCinternal -> addComponent(new capacitor("C902",  0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDCinternal -> addComponent(new capacitor("C903",  0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDCinternal -> addComponent(new capacitor("C904",  0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDCinternal -> addComponent(new capacitor("C905",  0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDCinternal -> addComponent(new capacitor("C906",  0.04, 40, 0.07, 120, capacitor::FITe9));

    DCDCinternal -> addComponent(new resistor("R900", 0.1, 40, resistor::FITe9 ));
    DCDCinternal -> addComponent(new resistor("R901", 0.1, 40, resistor::FITe9 ));
    DCDCinternal -> addComponent(new resistor("R902", 0.1, 40, resistor::FITe9 ));

    DCDCinternal -> addComponent(new inductor("L900",1.3,inductor::FITe9));

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

    DCDC18 -> addComponent(new capacitor("C500", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC18 -> addComponent(new capacitor("C501", 0.04, 40, 0.07, 120, capacitor::FITe9));

    DCDC18 -> addComponent(new inductor("L500",1.3, inductor::FITe9));

    ///DCDC 3.3V for Analog Part

    schematic* DCDC33A = new schematic("JUNO DC/DC 3.3V for Analog Part");

    // http://www.ti.com/quality/docs/estimator.tsp?OPN=TPS5432DDA&CPN=&partNumber=TPS5432DDA#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=TPS5432DDAR&CPN=&partNumber=TPS5432DDA#resultstable
    DCDC33A -> addComponent(new IC("TPS5432DDA", 18, IC::DPPM, 1e10, 55, IC::MTTF));

    DCDC33A -> addComponent(new capacitor("C600", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC33A -> addComponent(new capacitor("C601", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC33A -> addComponent(new capacitor("C602", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC33A -> addComponent(new capacitor("C603", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC33A -> addComponent(new capacitor("C604", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC33A -> addComponent(new capacitor("C605", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC33A -> addComponent(new capacitor("C606", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC33A -> addComponent(new capacitor("C607", 0.04, 40, 0.07, 120, capacitor::FITe9));

    DCDC33A -> addComponent(new resistor("R600", 0.1, 40, resistor::FITe9 ));
    DCDC33A -> addComponent(new resistor("R601", 0.1, 40, resistor::FITe9 ));
    DCDC33A -> addComponent(new resistor("R602", 0.1, 40, resistor::FITe9 ));
    DCDC33A -> addComponent(new resistor("R603", 0.1, 40, resistor::FITe9 ));
    DCDC33A -> addComponent(new resistor("R604", 0.1, 40, resistor::FITe9 ));

    DCDC33A -> addComponent(new inductor("L600",1.3, inductor::FITe9));

    /// JUNO 3V3 DC/DC for cable handling

    schematic* DCDC33C = new schematic("JUNO DC/DC 3.3V for cable handling");

    DCDC33C -> addComponent(new IC("LM3673TL", 41, IC::DPPM, 1.42e8, 55, IC::MTTF));

    DCDC33C -> addComponent(new capacitor("C800", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC33C -> addComponent(new capacitor("C801", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC33C -> addComponent(new capacitor("C802", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC33C -> addComponent(new capacitor("C803", 0.04, 40, 0.07, 120, capacitor::FITe9));

    DCDC33C -> addComponent(new resistor("R800", 0.1, 40, resistor::FITe9 ));
    DCDC33C -> addComponent(new resistor("R801", 0.1, 40, resistor::FITe9 ));

    DCDC33C -> addComponent(new inductor("L800",1.3, inductor::FITe9));

    /// JUNO 2V5 DC/DC for cable handling

    schematic* DCDC25C = new schematic("JUNO DC/DC 1.8V for cable handling");

    DCDC25C -> addComponent(new IC("LM3673TL", 41, IC::DPPM, 1.42e8, 55, IC::MTTF));

    DCDC25C -> addComponent(new capacitor("C700", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC25C -> addComponent(new capacitor("C701", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDC25C -> addComponent(new capacitor("C702", 0.04, 40, 0.07, 120, capacitor::FITe9));

    DCDC25C -> addComponent(new resistor("R700", 0.1, 40, resistor::FITe9 ));
    DCDC25C -> addComponent(new resistor("R701", 0.1, 40, resistor::FITe9 ));

    DCDC25C -> addComponent(new inductor("L701",125, Iqual));


    /// POE DCDC 24V -> 12V

    schematic* DCDCPOE = new schematic("POE DCDC Converter");

    // http://www.ti.com/quality/docs/estimator.tsp?OPN=LMR24220TL/NOPB&CPN=&partNumber=LMR24220#resultstable
    // http://www.ti.com/quality/docs/estimator.tsp?OPN=LMR24220TLX/NOPB&CPN=&partNumber=LMR24220#resultstable
    DCDCPOE -> addComponent(new IC("LMR24220", 19, IC::DPPM, 5.54e8, 55 , IC::MTTF));

    DCDCPOE -> addComponent(new capacitor("C1000", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDCPOE -> addComponent(new capacitor("C1001",0.1, 40, 0.16, 120, capacitor::FITe9));
    DCDCPOE -> addComponent(new capacitor("C1002",0.1, 40, 0.16, 120, capacitor::FITe9));
    DCDCPOE -> addComponent(new capacitor("C1003",0.1, 40, 0.16, 120, capacitor::FITe9));
    DCDCPOE -> addComponent(new capacitor("C1004",0.1, 40, 0.16, 120, capacitor::FITe9));
    DCDCPOE -> addComponent(new capacitor("C1005", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDCPOE -> addComponent(new capacitor("C1006", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDCPOE -> addComponent(new capacitor("C1007", 0.04, 40, 0.07, 120, capacitor::FITe9));
    DCDCPOE -> addComponent(new capacitor("C1008", 0.04, 40, 0.07, 120, capacitor::FITe9));

    DCDCPOE -> addComponent(new resistor("R1001", 0.1, 40, resistor::FITe9 ));
    DCDCPOE -> addComponent(new resistor("R1000", 0.1, 40, resistor::FITe9 ));
    DCDCPOE -> addComponent(new resistor("R1002", 0.1, 40, resistor::FITe9 ));
    DCDCPOE -> addComponent(new resistor("R1003", 0.1, 40, resistor::FITe9 ));


    DCDCPOE -> addComponent(new inductor("L1000",1.3,inductor::FITe9));



    cout << "###############################################################################" << endl;
    cout << endl;

    ///Combine everything - Power board

    schematic* PowerBoard = new schematic("Power Board");

    PowerBoard -> addComponent(new inductor("L1",1.3,inductor::FITe9));
    PowerBoard -> addComponent(new inductor("L2",1.3,inductor::FITe9));
    PowerBoard -> addComponent(new inductor("L3",1.3,inductor::FITe9));
    PowerBoard -> addComponent(new inductor("L4",1.3,inductor::FITe9));
    PowerBoard -> addComponent(new inductor("L5",1.3,inductor::FITe9));
    PowerBoard -> addComponent(new inductor("L6",1.3,inductor::FITe9));
    PowerBoard -> addComponent(new inductor("L7",1.3,inductor::FITe9));

    PowerBoard -> addComponent(new resistor("R1", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R2", 0.1, 40, resistor::FITe9 ));

    PowerBoard -> addComponent(new resistor("R3", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R4", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R5", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R6", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R7", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R8", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R9", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R10", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R11", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R12", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R13", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R14", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R15", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R16", 0.1, 40, resistor::FITe9 ));
    PowerBoard -> addComponent(new resistor("R17", 0.1, 40, resistor::FITe9 ));

    PowerBoard -> addComponent(new capacitor("C1", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C2", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C3", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C4", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C5", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C6", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C7", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C8", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C9", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C10", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C11", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C12", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C13", 0.04, 40, 0.07, 120, capacitor::FITe9));
    PowerBoard -> addComponent(new capacitor("C14", 0.04, 40, 0.07, 120, capacitor::FITe9));

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
    cout << "Weibull exponent determined from ICs: " << weibullExponentMean << " +/- " << weibullExponentError << std::endl;
    
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
