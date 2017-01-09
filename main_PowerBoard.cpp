#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor_WUERTH.h"
#include "resistor_VISHAY_CRCWe3.h"
#include "IC_TI.h"
#include "inductor_WUERTH.h"
#include "diode.h"
#include "PCB.h"

#include <cmath>


int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl;

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;

    // define the input voltages
    const float POCinput = 24.;
    const float POEinput = 48.;
    const float IntU = 6.;

/****************************************************************************************************************/
// JUNO Trigger Driver
    schematic* TriggerDriver = new schematic("JUNO Trigger Driver");
    TriggerDriver -> addComponent(new IC_TI("U100", "DS15BA101"));
    // input Cs
    TriggerDriver -> addComponent(new capacitor_WUERTH("C103", "WCAP-CSGP", 1*capacitor::uF, 1.5, 10));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C105", "WCAP-CSGP", 1*capacitor::uF, 1.5, 10));
    // output Cs
    TriggerDriver -> addComponent(new capacitor_WUERTH("C104", "WCAP-CSGP", 1*capacitor::uF, 2, 50));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C106", "WCAP-CSGP", 1*capacitor::uF, 2, 50));
    // 100n bypass Cs
    TriggerDriver -> addComponent(new capacitor_WUERTH("C100", "WCAP-CSGP", .1*capacitor::uF, 3.3, 16));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C101", "WCAP-CSGP", .1*capacitor::uF, 3.3, 16));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C102", "WCAP-CSGP", .1*capacitor::uF, 3.3, 16));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C107", "WCAP-CSGP", .1*capacitor::uF, 3.3, 16));
    TriggerDriver -> addComponent(new capacitor_WUERTH("C108", "WCAP-CSGP", .1*capacitor::nF, 3.3, 25));

    TriggerDriver -> addComponent(new resistor_VISHAY_CRCWe3("R104", 100*resistor::Ohm, 0.02, 0.1));
    TriggerDriver -> addComponent(new resistor_VISHAY_CRCWe3("R100", 953*resistor::Ohm, 0.05, 0.1));	// calculate stress
    TriggerDriver -> addComponent(new resistor_VISHAY_CRCWe3("R101", 50*resistor::Ohm, 0.05, 0.1));	// calculate stress
    TriggerDriver -> addComponent(new resistor_VISHAY_CRCWe3("R102", 50*resistor::Ohm, 0.05, 0.1));	// calculate stress

    TriggerDriver -> addComponent(new IC_TI("U101", "TPD2EUSB30DRTR"));
/****************************************************************************************************************/
// JUNO Clock Receiver
    schematic* CLKreceiver = new schematic("JUNO Clock Receiver");

    CLKreceiver -> addComponent(new IC_TI("U200", "DS15EA101"));
    // input C
    CLKreceiver -> addComponent(new capacitor_WUERTH("C200", "WCAP-CSGP", 1*capacitor::uF, POCinput, 50));
    CLKreceiver -> addComponent(new capacitor_WUERTH("C203", "WCAP-CSGP", 1*capacitor::uF, POCinput, 50));
    // second stage input C
    CLKreceiver -> addComponent(new capacitor_WUERTH("C201", "WCAP-CSGP", 1*capacitor::uF, 1.5, 10));	// check voltage
    CLKreceiver -> addComponent(new capacitor_WUERTH("C204", "WCAP-CSGP", 1*capacitor::uF, 1.5, 10));
    // output Cs
    CLKreceiver -> addComponent(new capacitor_WUERTH("C202", "WCAP-CSGP", 1*capacitor::uF, 1.5, 10));
    CLKreceiver -> addComponent(new capacitor_WUERTH("C205", "WCAP-CSGP", 1*capacitor::uF, 1.5, 10));
    // internal capacitor (CAP+ CAP-)
    CLKreceiver -> addComponent(new capacitor_WUERTH("C206", "WCAP-CSGP", 1*capacitor::uF, 1, 10));	// check voltage
    // bypass Cs (all at 3V3) 100n / 100p
    CLKreceiver -> addComponent(new capacitor_WUERTH("C209", "WCAP-CSGP", .1*capacitor::uF, 3.3, 16));
    CLKreceiver -> addComponent(new capacitor_WUERTH("C210", "WCAP-CSGP", .1*capacitor::uF, 3.3, 16));
    CLKreceiver -> addComponent(new capacitor_WUERTH("C211", "WCAP-CSGP", .1*capacitor::nF, 3.3, 10));
    CLKreceiver -> addComponent(new capacitor_WUERTH("C212", "WCAP-CSGP", .1*capacitor::nF, 3.3, 10));

    CLKreceiver -> addComponent(new resistor_VISHAY_CRCWe3("R201", 10*resistor::kOhm, 0.06, 0.1));	// calculate stress
    CLKreceiver -> addComponent(new resistor_VISHAY_CRCWe3("R203", 10*resistor::kOhm, 0.06, 0.1));
    CLKreceiver -> addComponent(new IC_TI("U201", "TPD2EUSB30DRTR"));
    
/****************************************************************************************************************/
// power splitting etc.
    schematic* CLKPowerSplitting = new schematic("CLK decoupling");
    // bypass Cs at 24V
    CLKPowerSplitting -> addComponent(new capacitor_WUERTH("C207", "WCAP-CSGP", .1*capacitor::uF, IntU, 50));
    CLKPowerSplitting -> addComponent(new capacitor_WUERTH("C208", "WCAP-CSGP", .1*capacitor::uF, IntU, 50));

    CLKPowerSplitting -> addComponent(new inductor_WUERTH("L200", "WE-CBF"));
    CLKPowerSplitting -> addComponent(new inductor_WUERTH("L201", "WE-CBF"));
    CLKPowerSplitting -> addComponent(new inductor_WUERTH("L202", "WE-SL5"));

/****************************************************************************************************************/
// cable supply 3V3
    schematic* C3V3 = new schematic("C3V3");
    C3V3 -> addComponent(new capacitor_WUERTH("C612", "WCAP-CSGP", .1*capacitor::nF,  IntU, 25));
    C3V3 -> addComponent(new capacitor_WUERTH("C613", "WCAP-CSGP", .1*capacitor::nF,  IntU, 25));
    C3V3 -> addComponent(new capacitor_WUERTH("C614", "WCAP-CSGP", 4.7*capacitor::uF, IntU, 16));
    C3V3 -> addComponent(new capacitor_WUERTH("C615", "WCAP-CSGP", 4.7*capacitor::uF, IntU, 16));
    C3V3 -> addComponent(new IC_TI("U600", "LM46000"));

    float I_R603_R605 = IntU / (330E3 + 470E3);
    C3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R603", 330*resistor::kOhm, pow(I_R603_R605,2)*330E3, 0.1)); 
    C3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R605", 470*resistor::kOhm, pow(I_R603_R605,2)*470E3, 0.1)); 
  
// supply for LVDS isolator 
    C3V3 -> addComponent(new IC_TI("U601", "TLV70225"));
    C3V3 -> addComponent(new capacitor_WUERTH("C626", "WCAP-CSGP", 1*capacitor::uF, 3.3, 50));
    C3V3 -> addComponent(new capacitor_WUERTH("C627", "WCAP-CSGP", 1*capacitor::uF, 2.5, 50));

/****************************************************************************************************************/
    schematic* IntVoltage = new schematic("Internal Voltage");
    IntVoltage -> addComponent(new IC_TI("U600", "LM46000"));

/****************************************************************************************************************/
// POE+ p. 8
    schematic* POE = new schematic("POE power");
    POE -> addComponent(new resistor_VISHAY_CRCWe3("R1100", 75*resistor::Ohm, 0.05, 0.1)); 
    POE -> addComponent(new resistor_VISHAY_CRCWe3("R1101", 75*resistor::Ohm, 0.05, 0.1)); 
    POE -> addComponent(new capacitor_WUERTH("C1101", "WCAP-CSGP", 1*capacitor::nF, POEinput/2., 50));
    POE -> addComponent(new capacitor_WUERTH("C1102", "WCAP-CSGP", 1*capacitor::nF, POEinput/2., 50));
    POE -> addComponent(new capacitor_WUERTH("C1104", "WCAP-CSGP", 1*capacitor::nF, POEinput/2., 50));

    POE -> addComponent(new inductor_WUERTH("T1100", "WE-PoE+"));
 
    POE -> addComponent(new resistor_VISHAY_CRCWe3("R1102", 75*resistor::Ohm, 0.05, 0.1)); 
    POE -> addComponent(new resistor_VISHAY_CRCWe3("R1103", 75*resistor::Ohm, 0.05, 0.1)); 
    POE -> addComponent(new capacitor_WUERTH("C1103", "WCAP-CSGP", 1*capacitor::nF, POEinput/2., 50));

    POE -> addComponent(new capacitor_WUERTH("C1100", "WCAP-CSGP", 100*capacitor::nF, POEinput, 50));
    POE -> addComponent(new inductor_WUERTH("L1100", "WE-SL5"));
    POE -> addComponent(new capacitor_WUERTH("C1105", "WCAP-CSGP", 100*capacitor::nF, POEinput, 50));

//TODO FIXME include diode D1100

/****************************************************************************************************************/
// DC/DC for GCU supply p. 9
    schematic* GCU_U = new schematic("GCU DC/DC");
    GCU_U -> addComponent(new capacitor_WUERTH("C1200", "WCAP-CSGP", 100*capacitor::pF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1205", "WCAP-CSGP", 100*capacitor::pF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1203", "WCAP-CSGP", 4.7*capacitor::uF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1208", "WCAP-CSGP", 4.7*capacitor::uF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1204", "WCAP-CSGP", 4.7*capacitor::uF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1209", "WCAP-CSGP", 4.7*capacitor::uF, POEinput/2., 50));
    GCU_U -> addComponent(new resistor_VISHAY_CRCWe3("R1200", 47*resistor::kOhm, pow(POEinput/2.,2)/47E3, 0.1)); 
    GCU_U -> addComponent(new resistor_VISHAY_CRCWe3("R1201", 47*resistor::kOhm, pow(POEinput/2.,2)/47E3, 0.1)); 

    GCU_U -> addComponent(new capacitor_WUERTH("C1218", "WCAP-CSGP", 100*capacitor::pF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1229", "WCAP-CSGP", 100*capacitor::pF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1219", "WCAP-CSGP", 100*capacitor::pF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1230", "WCAP-CSGP", 100*capacitor::pF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1220", "WCAP-CSGP", 4.7*capacitor::uF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1231", "WCAP-CSGP", 4.7*capacitor::uF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1221", "WCAP-CSGP", 4.7*capacitor::uF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1232", "WCAP-CSGP", 4.7*capacitor::uF, POEinput/2., 50));
    GCU_U -> addComponent(new resistor_VISHAY_CRCWe3("R1203", 47*resistor::kOhm, pow(POEinput/2.,2)/47E3, 0.1)); 
    GCU_U -> addComponent(new resistor_VISHAY_CRCWe3("R1207", 47*resistor::kOhm, pow(POEinput/2.,2)/47E3, 0.1)); 

    GCU_U -> addComponent(new IC_TI("U1200", "LM46002"));

    // enable + startup
    float I_R1202_R1205 = POEinput / (820e3 + 100e3);
    GCU_U -> addComponent(new resistor_VISHAY_CRCWe3("R1202", 820*resistor::kOhm, pow(I_R1202_R1205,2)*820E3, 0.1)); 
    GCU_U -> addComponent(new resistor_VISHAY_CRCWe3("R1205", 100*resistor::kOhm, pow(I_R1202_R1205,2)*100E3, 0.1)); 
    GCU_U -> addComponent(new capacitor_WUERTH("C1226", "WCAP-CSGP", 47*capacitor::nF, 5, 25)); // TODO

    // feedback
    float I_R1208_R1209 = 12. / (91E3 + 1000E3);
    GCU_U -> addComponent(new resistor_VISHAY_CRCWe3("R1202", 91*resistor::kOhm, pow(I_R1208_R1209,2)*91E3, 0.1)); 
    GCU_U -> addComponent(new resistor_VISHAY_CRCWe3("R1205", 1*resistor::MOhm, pow(I_R1208_R1209,2)*1E6, 0.1)); 
    GCU_U -> addComponent(new capacitor_WUERTH("C1235", "WCAP-CSGP", 68*capacitor::pF, 12, 50));

    GCU_U -> addComponent(new capacitor_WUERTH("C1210", "WCAP-CSGP", 1*capacitor::uF, POEinput/2., 50));
    GCU_U -> addComponent(new capacitor_WUERTH("C1211", "WCAP-CSGP", 1*capacitor::uF, POEinput/2., 50));

    GCU_U -> addComponent(new inductor_WUERTH("L1200", "WE-PD"));

    GCU_U -> addComponent(new capacitor_WUERTH("C1227", "WCAP-CSGP", 2.2*capacitor::uF, 5., 25));   // TODO voltage
    GCU_U -> addComponent(new capacitor_WUERTH("C1228", "WCAP-CSGP", 2.2*capacitor::uF, 12., 25));

    GCU_U -> addComponent(new capacitor_WUERTH("C1212", "WCAP-CSGP", 10*capacitor::uF, 12., 25));
    GCU_U -> addComponent(new capacitor_WUERTH("C1213", "WCAP-CSGP", 10*capacitor::uF, 12., 25));
    GCU_U -> addComponent(new capacitor_WUERTH("C1214", "WCAP-CSGP", 10*capacitor::uF, 12., 25));
    GCU_U -> addComponent(new capacitor_WUERTH("C1215", "WCAP-CSGP", 10*capacitor::uF, 12., 25));
    GCU_U -> addComponent(new capacitor_WUERTH("C1224", "WCAP-CSGP", 100*capacitor::pF, 12., 25));
    GCU_U -> addComponent(new capacitor_WUERTH("C1225", "WCAP-CSGP", 100*capacitor::pF, 12., 25));

    GCU_U -> addComponent(new resistor_VISHAY_CRCWe3("R1204", 68*resistor::kOhm, 0.05, 0.1)); 
    GCU_U -> addComponent(new resistor_VISHAY_CRCWe3("R1206", 12*resistor::kOhm, 0.05, 0.1)); 
    
/****************************************************************************************************************/
// I2C isolation p. 10
    schematic* I2Ciso = new schematic("I2C isolator");
    I2Ciso -> addComponent(new IC_TI("U1400", "ISO1541"));
    I2Ciso -> addComponent(new resistor_VISHAY_CRCWe3("R1402", 1*resistor::kOhm, pow(3.3,2)/1E3, 0.1)); 
    I2Ciso -> addComponent(new resistor_VISHAY_CRCWe3("R1403", 1*resistor::kOhm, pow(3.3,2)/1E3, 0.1)); 
    I2Ciso -> addComponent(new capacitor_WUERTH("C1400", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));
    I2Ciso -> addComponent(new capacitor_WUERTH("C1401", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));

    I2Ciso -> addComponent(new capacitor_WUERTH("C1404", "WCAP-CSGP", 100*capacitor::nF, 12., 50));
    I2Ciso -> addComponent(new capacitor_WUERTH("C1403", "WCAP-CSGP", 10*capacitor::uF, 12., 25));
    I2Ciso -> addComponent(new IC_TI("U1401", "LM9076"));
    I2Ciso -> addComponent(new capacitor_WUERTH("C1402", "WCAP-CSGP", 10*capacitor::uF, 3.3, 10));
    I2Ciso -> addComponent(new capacitor_WUERTH("C1405", "WCAP-CSGP", 1*capacitor::nF, 3.3, 25)); // TODO voltage?
    I2Ciso -> addComponent(new resistor_VISHAY_CRCWe3("R1404", 1.2, 0.05, 0.1)); // TODO Stress??

/****************************************************************************************************************/
// GCU monitoring p. 12
    schematic* GCUmonitoring = new schematic("GCU monitoring");
    GCUmonitoring -> addComponent(new capacitor_WUERTH("C1303", "WCAP-CSGP", 330*capacitor::nF, POEinput/2., 50));
    GCUmonitoring -> addComponent(new capacitor_WUERTH("C1309", "WCAP-CSGP", 330*capacitor::nF, POEinput/2., 50));
    //FIXME TODO  use the right inductor here
//    GCUmonitoring -> addComponent(new inductor_WUERTH("L1300", "WE-CSL"));
    GCUmonitoring -> addComponent(new capacitor_WUERTH("C1302", "WCAP-CSGP", 330*capacitor::nF, POEinput/2., 50));
    GCUmonitoring -> addComponent(new capacitor_WUERTH("C1308", "WCAP-CSGP", 330*capacitor::nF, POEinput/2., 50));

    float I_R1302_R1305 = POEinput / (56E3 + 2.2E3);
    GCUmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1302", 56*resistor::kOhm, pow(I_R1302_R1305,2) * 56E3, 0.1));
    GCUmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1302", 2.2*resistor::kOhm, pow(I_R1302_R1305,2)*2.2E3, 0.1));

    GCUmonitoring -> addComponent(new IC_TI("U1303", "INA168"));
    //FIXME TODO insert maximal current here
    GCUmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1301", 150*resistor::kOhm, pow(200E-6,2)*150E3, 0.1));

    GCUmonitoring -> addComponent(new IC_TI("U1302", "TLV2316"));
    GCUmonitoring -> addComponent(new capacitor_WUERTH("C1305", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));

    float I_R1300_R1309 = 3.3 / (100 + 47e3);
    GCUmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1300", 100*resistor::Ohm, pow(I_R1300_R1309,2)*100, 0.1));
    GCUmonitoring -> addComponent(new capacitor_WUERTH("C1304", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));
    GCUmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1309", 47*resistor::kOhm, pow(I_R1300_R1309,2)*47e3, 0.1));

    GCUmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1307", 100*resistor::Ohm, pow(I_R1300_R1309,2)*100, 0.1));
    GCUmonitoring -> addComponent(new capacitor_WUERTH("C1306", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));
    GCUmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1310", 47*resistor::kOhm, pow(I_R1300_R1309,2)*47e3, 0.1));

    GCUmonitoring -> addComponent(new IC_TI("U1304", "ADS1015"));
    GCUmonitoring -> addComponent(new capacitor_WUERTH("C1307", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));
    GCUmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1306", 0*resistor::Ohm, 0, 0.1)); // FIXME

/****************************************************************************************************************/
// Temperature Monitoring p. 13
    schematic* Tmonitoring = new schematic("Temp monitoring");
    Tmonitoring -> addComponent(new IC_TI("U1", "LM75"));
    Tmonitoring -> addComponent(new capacitor_WUERTH("C1", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));
    Tmonitoring -> addComponent(new IC_TI("U1300", "LM75"));
    Tmonitoring -> addComponent(new capacitor_WUERTH("C1300", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));

/****************************************************************************************************************/
// put the whole thing together
    schematic* PowerBoard = new schematic("Power Board (total)");

    PowerBoard -> addComponent(new PCB("PowerBoard v2", 4, 126, PCB::THROUGH_HOLE, 200));
    PowerBoard -> addComponent(TriggerDriver);
    PowerBoard -> addComponent(CLKreceiver);
    PowerBoard -> addComponent(CLKPowerSplitting);
    PowerBoard -> addComponent(C3V3);

    PowerBoard -> addComponent(POE);
    PowerBoard -> addComponent(GCU_U);
    // GCU_U -> setVerboseOutput(true);
    PowerBoard -> addComponent(I2Ciso);

    PowerBoard -> addComponent(GCUmonitoring);
    PowerBoard -> addComponent(Tmonitoring);

    PowerBoard -> setVerboseOutput(true);

/****************************************************************************************************************/
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
