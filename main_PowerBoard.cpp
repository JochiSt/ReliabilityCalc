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
// filtering  p. 1
    schematic* filter = new schematic("Vcc Filtering");
    filter -> addComponent(new inductor_WUERTH("L1", "WE-SL5"));
    filter -> addComponent(new capacitor_WUERTH("C4", "WCAP-CSGP", .1*capacitor::uF, POCinput, 50));

    // if used with Tsinghua C7 L3 C8
    filter -> addComponent(new capacitor_WUERTH("C5", "WCAP-CSGP", .1*capacitor::uF, IntU, 50));
    filter -> addComponent(new inductor_WUERTH("L2", "WE-SL5"));
    filter -> addComponent(new capacitor_WUERTH("C6", "WCAP-CSGP", .1*capacitor::uF, IntU, 50));

/****************************************************************************************************************/
// JUNO Trigger Driver p. 2
    schematic* TriggerDriver = new schematic("Sync TX");
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
// JUNO Clock Receiver p. 3
    schematic* CLKreceiver = new schematic("Sync RX");

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
// power splitting etc. p. 3
    schematic* CLKPowerSplitting = new schematic("CLK decoupling");
    // bypass Cs at 24V
    CLKPowerSplitting -> addComponent(new capacitor_WUERTH("C207", "WCAP-CSGP", .1*capacitor::uF, IntU, 50));
    CLKPowerSplitting -> addComponent(new capacitor_WUERTH("C208", "WCAP-CSGP", .1*capacitor::uF, IntU, 50));

    CLKPowerSplitting -> addComponent(new inductor_WUERTH("L200", "WE-CBF"));
    CLKPowerSplitting -> addComponent(new inductor_WUERTH("L201", "WE-CBF"));
    CLKPowerSplitting -> addComponent(new inductor_WUERTH("L202", "WE-SL5"));

/****************************************************************************************************************/
// cable supply 3V3 p. 4
    schematic* C3V3 = new schematic("C3V3");
  
    C3V3 -> addComponent(new capacitor_WUERTH("C612", "WCAP-CSGP", .1*capacitor::nF,  IntU, 25));
    C3V3 -> addComponent(new capacitor_WUERTH("C613", "WCAP-CSGP", .1*capacitor::nF,  IntU, 25));
    C3V3 -> addComponent(new capacitor_WUERTH("C614", "WCAP-CSGP", 4.7*capacitor::uF, IntU, 16));
    C3V3 -> addComponent(new capacitor_WUERTH("C615", "WCAP-CSGP", 4.7*capacitor::uF, IntU, 16));
    
    // enable + startup
    float I_R603_R605 = IntU / (330e3 + 470e3);
    C3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R603", 330*resistor::kOhm, pow(I_R603_R605,2)*330E3, 0.1)); 
    C3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R605", 470*resistor::kOhm, pow(I_R603_R605,2)*470E3, 0.1)); 
    C3V3 -> addComponent(new capacitor_WUERTH("C618", "WCAP-CSGP", 47*capacitor::nF, 5, 25)); // TODO

    C3V3 -> addComponent(new IC_TI("U600", "LM46000"));

    // feedback
    float I_R608_R609 = 3.3 / (1E6 + 442E3);
    C3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R608", 442*resistor::kOhm, pow(I_R608_R609,2)*442E3, 0.1)); 
    C3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R609", 1*resistor::MOhm, pow(I_R608_R609,2)*1e6, 0.1)); 
    C3V3 -> addComponent(new capacitor_WUERTH("C621", "WCAP-CSGP", 68*capacitor::pF, 3.3, 50));

    C3V3 -> addComponent(new capacitor_WUERTH("C603", "WCAP-CSGP", 470*capacitor::nF, IntU, 25));

    C3V3 -> addComponent(new inductor_WUERTH("L600", "WE-PD"));

    C3V3 -> addComponent(new capacitor_WUERTH("C619", "WCAP-CSGP", 2.2*capacitor::uF, 5, 25));	// TODO
    C3V3 -> addComponent(new capacitor_WUERTH("C620", "WCAP-CSGP", 2.2*capacitor::uF, 3.3, 25));

    C3V3 -> addComponent(new capacitor_WUERTH("C604", "WCAP-CSGP", 10*capacitor::uF, 3.3, 10));
    C3V3 -> addComponent(new capacitor_WUERTH("C605", "WCAP-CSGP", 10*capacitor::uF, 3.3, 10));
    C3V3 -> addComponent(new capacitor_WUERTH("C606", "WCAP-CSGP", 10*capacitor::uF, 3.3, 10));
    C3V3 -> addComponent(new capacitor_WUERTH("C607", "WCAP-CSGP", 10*capacitor::uF, 3.3, 10));
    C3V3 -> addComponent(new capacitor_WUERTH("C610", "WCAP-CSGP", 100*capacitor::pF, 3.3, 25));
    C3V3 -> addComponent(new capacitor_WUERTH("C611", "WCAP-CSGP", 100*capacitor::pF, 3.3, 25));

    // frequency
    C3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R604", 56*resistor::kOhm, 0.05, 0.1)); 
    C3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R606", 10*resistor::kOhm, 0.05, 0.1)); 

    // output filter
    C3V3 -> addComponent(new capacitor_WUERTH("C622", "WCAP-CSGP", 4.7*capacitor::uF, 3.3, 16));
    C3V3 -> addComponent(new capacitor_WUERTH("C623", "WCAP-CSGP", 100*capacitor::pF, 3.3, 25));
    C3V3 -> addComponent(new inductor_WUERTH("L601", "WE-CBF"));
    C3V3 -> addComponent(new capacitor_WUERTH("C624", "WCAP-CSGP", 100*capacitor::pF, 3.3, 25));
    C3V3 -> addComponent(new capacitor_WUERTH("C625", "WCAP-CSGP", 4.7*capacitor::uF, 3.3, 16));

// supply for LVDS isolator 
    C3V3 -> addComponent(new IC_TI("U601", "TLV70225"));
    C3V3 -> addComponent(new capacitor_WUERTH("C626", "WCAP-CSGP", 1*capacitor::uF, 3.3, 50));
    C3V3 -> addComponent(new capacitor_WUERTH("C627", "WCAP-CSGP", 1*capacitor::uF, 2.5, 50));

/****************************************************************************************************************/
// Analog 1V8 supply p. 5
    schematic* A1V8  = new schematic("analog 1V8");

    A1V8 -> addComponent(new capacitor_WUERTH("C412", "WCAP-CSGP", .1*capacitor::nF,  IntU, 25));
    A1V8 -> addComponent(new capacitor_WUERTH("C413", "WCAP-CSGP", .1*capacitor::nF,  IntU, 25));
    A1V8 -> addComponent(new capacitor_WUERTH("C414", "WCAP-CSGP", 4.7*capacitor::uF, IntU, 16));
    A1V8 -> addComponent(new capacitor_WUERTH("C415", "WCAP-CSGP", 4.7*capacitor::uF, IntU, 16));
    
    // enable + startup
    A1V8 -> addComponent(new resistor_VISHAY_CRCWe3("R1", 10*resistor::kOhm, 0.05, 0.1)); 
    A1V8 -> addComponent(new capacitor_WUERTH("C418", "WCAP-CSGP", 47*capacitor::nF, 5, 25)); // TODO

    A1V8 -> addComponent(new IC_TI("U400", "LM46000"));

    // feedback
    float I_R408_R409 = 1.8 / (1E6 + 1.27E6);
    A1V8 -> addComponent(new resistor_VISHAY_CRCWe3("R408", 442*resistor::kOhm, pow(I_R408_R409,2)*442E3, 0.1)); 
    A1V8 -> addComponent(new resistor_VISHAY_CRCWe3("R409", 1*resistor::MOhm, pow(I_R408_R409,2)*1e6, 0.1)); 
    A1V8 -> addComponent(new capacitor_WUERTH("C421", "WCAP-CSGP", 68*capacitor::pF, 1.8, 50));

    A1V8 -> addComponent(new capacitor_WUERTH("C403", "WCAP-CSGP", 470*capacitor::nF, IntU, 25));

    A1V8 -> addComponent(new inductor_WUERTH("L400", "WE-PD"));

    A1V8 -> addComponent(new capacitor_WUERTH("C419", "WCAP-CSGP", 2.2*capacitor::uF, 5, 25));	// TODO
    A1V8 -> addComponent(new capacitor_WUERTH("C420", "WCAP-CSGP", 2.2*capacitor::uF, 3.3, 25));

    A1V8 -> addComponent(new capacitor_WUERTH("C404", "WCAP-CSGP", 10*capacitor::uF, 1.8, 10));
    A1V8 -> addComponent(new capacitor_WUERTH("C405", "WCAP-CSGP", 10*capacitor::uF, 1.8, 10));
    A1V8 -> addComponent(new capacitor_WUERTH("C406", "WCAP-CSGP", 10*capacitor::uF, 1.8, 10));
    A1V8 -> addComponent(new capacitor_WUERTH("C407", "WCAP-CSGP", 10*capacitor::uF, 1.8, 10));
    A1V8 -> addComponent(new capacitor_WUERTH("C410", "WCAP-CSGP", 100*capacitor::pF, 1.8, 25));
    A1V8 -> addComponent(new capacitor_WUERTH("C411", "WCAP-CSGP", 100*capacitor::pF, 1.8, 25));

    // frequency
    A1V8 -> addComponent(new resistor_VISHAY_CRCWe3("R403", 33*resistor::kOhm, 0.05, 0.1)); 
    A1V8 -> addComponent(new resistor_VISHAY_CRCWe3("R404", 10*resistor::kOhm, 0.05, 0.1)); 

    // output filter
    A1V8 -> addComponent(new capacitor_WUERTH("C422", "WCAP-CSGP", 4.7*capacitor::uF, 1.8, 16));
    A1V8 -> addComponent(new capacitor_WUERTH("C423", "WCAP-CSGP", 100*capacitor::pF, 1.8, 25));
    A1V8 -> addComponent(new inductor_WUERTH("L401", "WE-CBF"));
    A1V8 -> addComponent(new capacitor_WUERTH("C424", "WCAP-CSGP", 100*capacitor::pF, 1.8, 25));
    A1V8 -> addComponent(new capacitor_WUERTH("C425", "WCAP-CSGP", 4.7*capacitor::uF, 1.8, 16));

/****************************************************************************************************************/
// Analog 3V3 supply p. 6
    schematic* A3V3  = new schematic("analog 3V3");

    A3V3 -> addComponent(new capacitor_WUERTH("C512", "WCAP-CSGP", .1*capacitor::nF,  IntU, 25));
    A3V3 -> addComponent(new capacitor_WUERTH("C513", "WCAP-CSGP", .1*capacitor::nF,  IntU, 25));
    A3V3 -> addComponent(new capacitor_WUERTH("C514", "WCAP-CSGP", 4.7*capacitor::uF, IntU, 16));
    A3V3 -> addComponent(new capacitor_WUERTH("C515", "WCAP-CSGP", 4.7*capacitor::uF, IntU, 16));
    
    // enable + startup
    float I_R503_R505 = IntU / (330e3 + 470e3);
    A3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R503", 820*resistor::kOhm, pow(I_R503_R505,2)*330E3, 0.1)); 
    A3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R305", 100*resistor::kOhm, pow(I_R503_R505,2)*470E3, 0.1)); 
    A3V3 -> addComponent(new capacitor_WUERTH("C518", "WCAP-CSGP", 47*capacitor::nF, 5, 25)); // TODO

    A3V3 -> addComponent(new IC_TI("U500", "LM46000"));

    // feedback
    float I_R510_R511 = 3.3 / (1E6 + 442E3);
    A3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R510", 442*resistor::kOhm, pow(I_R510_R511,2)*442E3, 0.1)); 
    A3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R511", 1*resistor::MOhm, pow(I_R510_R511,2)*1e6, 0.1)); 
    A3V3 -> addComponent(new capacitor_WUERTH("C521", "WCAP-CSGP", 68*capacitor::pF, 3.3, 50));

    A3V3 -> addComponent(new capacitor_WUERTH("C503", "WCAP-CSGP", 470*capacitor::nF, IntU, 25));

    A3V3 -> addComponent(new inductor_WUERTH("L500", "WE-PD"));

    A3V3 -> addComponent(new capacitor_WUERTH("C519", "WCAP-CSGP", 2.2*capacitor::uF, 5, 25));	// TODO
    A3V3 -> addComponent(new capacitor_WUERTH("C520", "WCAP-CSGP", 2.2*capacitor::uF, 3.3, 25));

    A3V3 -> addComponent(new capacitor_WUERTH("C504", "WCAP-CSGP", 10*capacitor::uF, 3.3, 10));
    A3V3 -> addComponent(new capacitor_WUERTH("C505", "WCAP-CSGP", 10*capacitor::uF, 3.3, 10));
    A3V3 -> addComponent(new capacitor_WUERTH("C506", "WCAP-CSGP", 10*capacitor::uF, 3.3, 10));
    A3V3 -> addComponent(new capacitor_WUERTH("C507", "WCAP-CSGP", 10*capacitor::uF, 3.3, 10));
    A3V3 -> addComponent(new capacitor_WUERTH("C510", "WCAP-CSGP", 100*capacitor::pF, 3.3, 25));
    A3V3 -> addComponent(new capacitor_WUERTH("C511", "WCAP-CSGP", 100*capacitor::pF, 3.3, 25));

    // frequency
    A3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R504", 56*resistor::kOhm, 0.05, 0.1)); 
    A3V3 -> addComponent(new resistor_VISHAY_CRCWe3("R506", 10*resistor::kOhm, 0.05, 0.1)); 

    // output filter
    A3V3 -> addComponent(new capacitor_WUERTH("C522", "WCAP-CSGP", 4.7*capacitor::uF, 3.3, 16));
    A3V3 -> addComponent(new capacitor_WUERTH("C523", "WCAP-CSGP", 100*capacitor::pF, 3.3, 25));
    A3V3 -> addComponent(new inductor_WUERTH("L501", "WE-CBF"));
    A3V3 -> addComponent(new capacitor_WUERTH("C524", "WCAP-CSGP", 100*capacitor::pF, 3.3, 25));
    A3V3 -> addComponent(new capacitor_WUERTH("C525", "WCAP-CSGP", 4.7*capacitor::uF, 3.3, 16));

/****************************************************************************************************************/
// Internal Voltage p. 7
    schematic* Int_U = new schematic("Internal Voltage");

    Int_U -> addComponent(new capacitor_WUERTH("C307", "WCAP-CSGP", 100*capacitor::pF, POCinput, 50));
    Int_U -> addComponent(new capacitor_WUERTH("C308", "WCAP-CSGP", 100*capacitor::pF, POCinput, 50));
    Int_U -> addComponent(new capacitor_WUERTH("C309", "WCAP-CSGP", 4.7*capacitor::uF, POCinput, 50));
    Int_U -> addComponent(new capacitor_WUERTH("C310", "WCAP-CSGP", 4.7*capacitor::uF, POCinput, 50));
    Int_U -> addComponent(new capacitor_WUERTH("C311", "WCAP-CSGP", 4.7*capacitor::uF, POCinput, 50));
    Int_U -> addComponent(new capacitor_WUERTH("C312", "WCAP-CSGP", 4.7*capacitor::uF, POCinput, 50));

    // enable + startup
    float I_R300_R303 = POCinput / (820e3 + 100e3);
    Int_U -> addComponent(new resistor_VISHAY_CRCWe3("R300", 820*resistor::kOhm, pow(I_R300_R303,2)*820E3, 0.1)); 
    Int_U -> addComponent(new resistor_VISHAY_CRCWe3("R303", 100*resistor::kOhm, pow(I_R300_R303,2)*100E3, 0.1)); 
    Int_U -> addComponent(new capacitor_WUERTH("C315", "WCAP-CSGP", 47*capacitor::nF, 5, 25)); // TODO

    Int_U -> addComponent(new IC_TI("U600", "LM46000"));

    // feedback
    float I_R305_R306 = IntU / (910E3 + 180E3);
    Int_U -> addComponent(new resistor_VISHAY_CRCWe3("R305", 180*resistor::kOhm, pow(I_R305_R306,2)*910E3, 0.1)); 
    Int_U -> addComponent(new resistor_VISHAY_CRCWe3("R306", 910*resistor::kOhm, pow(I_R305_R306,2)*180E3, 0.1)); 
    Int_U -> addComponent(new capacitor_WUERTH("C318", "WCAP-CSGP", 68*capacitor::pF, 12, 50));

    Int_U -> addComponent(new capacitor_WUERTH("C300", "WCAP-CSGP", 470*capacitor::nF, POCinput, 50));

    Int_U -> addComponent(new inductor_WUERTH("L300", "WE-PD"));

    Int_U -> addComponent(new capacitor_WUERTH("C316", "WCAP-CSGP", 2.2*capacitor::uF, 5., 25));   // TODO voltage
    Int_U -> addComponent(new capacitor_WUERTH("C317", "WCAP-CSGP", 2.2*capacitor::uF, IntU, 25));

    Int_U -> addComponent(new capacitor_WUERTH("C301", "WCAP-CSGP", 10*capacitor::uF, IntU, 25));
    Int_U -> addComponent(new capacitor_WUERTH("C302", "WCAP-CSGP", 10*capacitor::uF, IntU, 25));
    Int_U -> addComponent(new capacitor_WUERTH("C303", "WCAP-CSGP", 10*capacitor::uF, IntU, 25));
    Int_U -> addComponent(new capacitor_WUERTH("C304", "WCAP-CSGP", 10*capacitor::uF, IntU, 25));
    Int_U -> addComponent(new capacitor_WUERTH("C305", "WCAP-CSGP", 10*capacitor::uF, IntU, 25));
    Int_U -> addComponent(new capacitor_WUERTH("C306", "WCAP-CSGP", 10*capacitor::uF, IntU, 25));
    Int_U -> addComponent(new capacitor_WUERTH("C313", "WCAP-CSGP", 100*capacitor::pF, IntU, 50));
    Int_U -> addComponent(new capacitor_WUERTH("C314", "WCAP-CSGP", 100*capacitor::pF, IntU, 50));

    // frequency
    Int_U -> addComponent(new resistor_VISHAY_CRCWe3("R302", 68*resistor::kOhm, 0.05, 0.1)); 
    Int_U -> addComponent(new resistor_VISHAY_CRCWe3("R304", 4.7*resistor::kOhm, 0.05, 0.1)); 

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

    float I_R1105_R1106 = POEinput / (47e3 + 47e3);
    POE -> addComponent(new capacitor_WUERTH("C1100", "WCAP-CSGP", 100*capacitor::nF, POEinput/2., 50));
    POE -> addComponent(new capacitor_WUERTH("C1106", "WCAP-CSGP", 100*capacitor::nF, POEinput/2., 50));
    POE -> addComponent(new inductor_WUERTH("L1100", "WE-SL5"));
    POE -> addComponent(new capacitor_WUERTH("C1105", "WCAP-CSGP", 100*capacitor::nF, POEinput/2., 50));
    POE -> addComponent(new capacitor_WUERTH("C1107", "WCAP-CSGP", 100*capacitor::nF, POEinput/2., 50));
    
    POE -> addComponent(new resistor_VISHAY_CRCWe3("R1105", 47*resistor::kOhm, pow(I_R1105_R1106,2)*47e3, 0.1));
    POE -> addComponent(new resistor_VISHAY_CRCWe3("R1106", 47*resistor::kOhm, pow(I_R1105_R1106,2)*47e3, 0.1));
    POE -> addComponent(new resistor_VISHAY_CRCWe3("R1107", 100*resistor::Ohm, 0.05, 0.1));


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
    
    // frequency
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
    I2Ciso -> addComponent(new resistor_VISHAY_CRCWe3("R1404", 1.2*resistor::Ohm, 0.05, 0.1)); // TODO Stress??

/****************************************************************************************************************/
// POC monitoring p. 11
    schematic* POCmonitoring = new schematic("POC monitoring");
    
    POCmonitoring -> addComponent(new capacitor_WUERTH("C904", "WCAP-CSGP", 100*capacitor::nF, POCinput, 50));
    POCmonitoring -> addComponent(new inductor_WUERTH("L900", "WE-CBF"));
    POCmonitoring -> addComponent(new capacitor_WUERTH("C903", "WCAP-CSGP", 100*capacitor::nF, POCinput, 50));

    float I_R902_R903 = POCinput / (47E3 + 2.7E3);
    POCmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R902", 47*resistor::kOhm, pow(I_R902_R903,2) * 47E3, 0.1));
    POCmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R903", 2.7*resistor::kOhm, pow(I_R902_R903,2)*2.7E3, 0.1));

    POCmonitoring -> addComponent(new IC_TI("U901", "INA168"));
    //FIXME TODO insert maximal current here
    POCmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R901", 390*resistor::kOhm, pow(200E-6,2)*390E3, 0.1));

    POCmonitoring -> addComponent(new IC_TI("U900", "TLV2316"));
    POCmonitoring -> addComponent(new capacitor_WUERTH("C901", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));

    float I_R900_R905 = 3.3 / (100 + 47e3);
    POCmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R900", 100*resistor::Ohm, pow(I_R900_R905,2)*100, 0.1));
    POCmonitoring -> addComponent(new capacitor_WUERTH("C900", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));
    POCmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R905", 47*resistor::kOhm, pow(I_R900_R905,2)*47e3, 0.1));

    POCmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R904", 100*resistor::Ohm, pow(I_R900_R905,2)*100, 0.1));
    POCmonitoring -> addComponent(new capacitor_WUERTH("C902", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));
    POCmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R906", 47*resistor::kOhm, pow(I_R900_R905,2)*47e3, 0.1));

    float I_R907_R908 = 6.0 / (27e3 + 12e3);
    POCmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R907", 27*resistor::kOhm, pow(I_R907_R908,2)*27e3, 0.1));
    POCmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R908", 12*resistor::kOhm, pow(I_R907_R908,2)*12e3, 0.1));

    POCmonitoring -> addComponent(new IC_TI("U3", "ADS1015"));
    POCmonitoring -> addComponent(new capacitor_WUERTH("C905", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));

/****************************************************************************************************************/
// POE monitoring p. 12
    schematic* POEmonitoring = new schematic("POE monitoring");
    POEmonitoring -> addComponent(new capacitor_WUERTH("C1303", "WCAP-CSGP", 330*capacitor::nF, POEinput/2., 50));
    POEmonitoring -> addComponent(new capacitor_WUERTH("C1309", "WCAP-CSGP", 330*capacitor::nF, POEinput/2., 50));
    POEmonitoring -> addComponent(new inductor_WUERTH("L1300", "WE-CBF"));
    POEmonitoring -> addComponent(new capacitor_WUERTH("C1302", "WCAP-CSGP", 330*capacitor::nF, POEinput/2., 50));
    POEmonitoring -> addComponent(new capacitor_WUERTH("C1308", "WCAP-CSGP", 330*capacitor::nF, POEinput/2., 50));

    float I_R1311_R1313 = POEinput / (47E3 + 47E3);
    POEmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1311", 47*resistor::kOhm, pow(I_R1311_R1313,2)*47E3, 0.1));
    POEmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1313", 47*resistor::kOhm, pow(I_R1311_R1313,2)*47E3, 0.1));
    POEmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1312", 100*resistor::Ohm, 0.05, 0.1));

    float I_R1302_R1305 = POEinput / (56E3 + 2.2E3);
    POEmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1302", 56*resistor::kOhm, pow(I_R1302_R1305,2) * 56E3, 0.1));
    POEmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1305", 2.2*resistor::kOhm, pow(I_R1302_R1305,2)*2.2E3, 0.1));

    POEmonitoring -> addComponent(new IC_TI("U1303", "INA168"));
    //FIXME TODO insert maximal current here
    POEmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1301", 150*resistor::kOhm, pow(200E-6,2)*150E3, 0.1));

    POEmonitoring -> addComponent(new IC_TI("U1302", "TLV2316"));
    POEmonitoring -> addComponent(new capacitor_WUERTH("C1305", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));

    float I_R1300_R1309 = 3.3 / (100 + 47e3);
    POEmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1300", 100*resistor::Ohm, pow(I_R1300_R1309,2)*100, 0.1));
    POEmonitoring -> addComponent(new capacitor_WUERTH("C1304", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));
    POEmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1309", 47*resistor::kOhm, pow(I_R1300_R1309,2)*47e3, 0.1));

    POEmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1307", 100*resistor::Ohm, pow(I_R1300_R1309,2)*100, 0.1));
    POEmonitoring -> addComponent(new capacitor_WUERTH("C1306", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));
    POEmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1310", 47*resistor::kOhm, pow(I_R1300_R1309,2)*47e3, 0.1));

    float I_R1314_R1315 = 12.0 / (39e3 + 6.8e3);
    POCmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1314", 27*resistor::kOhm, pow(I_R1314_R1315,2)*39e3, 0.1));
    POCmonitoring -> addComponent(new resistor_VISHAY_CRCWe3("R1315", 6.8*resistor::kOhm, pow(I_R1314_R1315,2)*6.8e3, 0.1));

    POEmonitoring -> addComponent(new IC_TI("U1304", "ADS1015"));
    POEmonitoring -> addComponent(new capacitor_WUERTH("C1307", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));

/****************************************************************************************************************/
// Temperature Monitoring p. 13
    schematic* Tmonitoring = new schematic("Temp monitoring");
    Tmonitoring -> addComponent(new IC_TI("U1", "TMP100"));
    Tmonitoring -> addComponent(new capacitor_WUERTH("C1", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));
    Tmonitoring -> addComponent(new IC_TI("U1300", "TMP100"));
    Tmonitoring -> addComponent(new capacitor_WUERTH("C1300", "WCAP-CSGP", 100*capacitor::nF, 3.3, 16));

/****************************************************************************************************************/
// put the whole thing together


    schematic* PowerBoard = new schematic("Power Board (total)");

    PowerBoard -> addComponent(new PCB("PowerBoard PCB", 4, 500, PCB::THROUGH_HOLE, 125));

    PowerBoard -> addComponent(filter);

    PowerBoard -> addComponent(TriggerDriver);
    PowerBoard -> addComponent(CLKreceiver);
    PowerBoard -> addComponent(CLKPowerSplitting);

    PowerBoard -> addComponent(C3V3);
    PowerBoard -> addComponent(A1V8);
    PowerBoard -> addComponent(A3V3);

    PowerBoard -> addComponent(Int_U);

    PowerBoard -> addComponent(POE);
    PowerBoard -> addComponent(GCU_U);
    // GCU_U -> setVerboseOutput(true);

    PowerBoard -> addComponent(I2Ciso);

    PowerBoard -> addComponent(POCmonitoring);
    PowerBoard -> addComponent(POEmonitoring);
    PowerBoard -> addComponent(Tmonitoring);

    PowerBoard -> setVerboseOutput(true);

/****************************************************************************************************************/
    cout << endl;
    cout << "Calculating FIT for " << component::getAmbientTemperature() - component::KELVIN << "°C" << endl;

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
