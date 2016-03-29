#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor.h"
#include "resistor.h"
#include "IC.h"
#include "inductor.h"
#include "diode.h"

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl;

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;

    schematic* CLKdecoupling = new schematic("Clock Decoupling");
    CLKdecoupling -> addComponent(new IC("IC1", 3.23e9, 55, IC::MTTF ));    ///AD8058
    CLKdecoupling -> addComponent(new IC("IC2", 3.23e9, 55, IC::MTTF ));    ///ADCMP553

    CLKdecoupling -> addComponent(new capacitor("C1", 100*capacitor::nF, 3.3, 25, 85, capacitor::Q_S ));
    CLKdecoupling -> addComponent(new capacitor("C2", 47*capacitor::pF, 24, 100, 85, capacitor::Q_S ));
    CLKdecoupling -> addComponent(new capacitor("C3", 100*capacitor::nF, 3.3, 25, 85, capacitor::Q_S ));
    CLKdecoupling -> addComponent(new capacitor("C4", 47*capacitor::pF, 24, 100, 85, capacitor::Q_S ));
    CLKdecoupling -> addComponent(new capacitor("C5", 1*capacitor::nF, 3.3, 25, 85, capacitor::Q_S ));
    CLKdecoupling -> addComponent(new capacitor("C6", 100*capacitor::nF, 3.3, 25, 85, capacitor::Q_S ));
    CLKdecoupling -> addComponent(new capacitor("C7", 100*capacitor::nF, 3.3, 25, 85, capacitor::Q_S ));
    CLKdecoupling -> addComponent(new capacitor("C9", 1*capacitor::nF, 3.3, 25, 85, capacitor::Q_S ));
    CLKdecoupling -> addComponent(new capacitor("C10", 1*capacitor::nF, 1.65, 25, 85, capacitor::Q_S ));
    CLKdecoupling -> addComponent(new capacitor("C11", 1*capacitor::nF, 3.3, 25, 85, capacitor::Q_S ));

    CLKdecoupling -> addComponent(new resistor("R2", 100*resistor::kOhm, 2.75e-5, 0.125, resistor::Q_S ));
    CLKdecoupling -> addComponent(new resistor("R3", 100*resistor::kOhm, 2.75e-5, 0.125, resistor::Q_S ));
    CLKdecoupling -> addComponent(new resistor("R4", 100*resistor::kOhm, 2.75e-5, 0.125, resistor::Q_S ));
    CLKdecoupling -> addComponent(new resistor("R5", 100*resistor::kOhm, 2.75e-5, 0.125, resistor::Q_S ));

    //CLKdecoupling -> addComponent(new inductor("L1", 125, inductor::Q_M ));
    //CLKdecoupling -> addComponent(new diode("D1",2,5,diode::SCHOTTKY,diode::Q_JAN));


    cout << "###############################################################################" << endl;
    cout << endl;

    component::environment = component::GF;

    double FIT = CLKdecoupling -> getFIT();

    cout << "Total FIT " << FIT << " / " << component::FITunit << endl;

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;

    cout << "Failures within 6 years: " << schematic::getFailureRate( 6 * component::YEAR, FIT ) * 100. << " %" << endl;


//######################################################################################################################

    CLKdecoupling -> exportToFile("test");      // save schematic in 'test'
    CLKdecoupling -> clear();                   // clear all parts
    CLKdecoupling -> importFromFile("test");    // re-import from 'test'
    CLKdecoupling -> exportToFile("test2");     // export to 'test2' -> at the end 'test' and 'test2' should be the same

    return 0;
}
