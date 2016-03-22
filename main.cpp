#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor.h"
#include "resistor.h"
#include "IC.h"
#include "inductor.h"

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl;

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;

    schematic* CLKdecoupling = new schematic("Clock Decoupling");
    CLKdecoupling -> addComponent(new capacitor("C1", 10*capacitor::nF, 5, 10, 85, capacitor::Q_M ));
    CLKdecoupling -> addComponent(new capacitor("C2", 10*capacitor::nF, 5, 10, 85, capacitor::Q_M ));
    CLKdecoupling -> addComponent(new resistor("R1", 10*resistor::kOhm, 0.1, 0.5, resistor::Q_M ));
    CLKdecoupling -> addComponent(new IC("IC1", 1.76e9, 55, IC::MTTF ));
    CLKdecoupling -> addComponent(new inductor("L1", 125, inductor::Q_M ));


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

    component::environment = component::GF;

    cout << "###############################################################################" << endl;
    cout << endl;

    FIT = CLKdecoupling -> getFIT();

    cout << "Total FIT " << FIT << " / " << component::FITunit << endl;

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;

    cout << "Failures within 6 years: " << schematic::getFailureRate( 6 * component::YEAR, FIT ) * 100. << " %" << endl;

    cout << endl;
    return 0;
}
