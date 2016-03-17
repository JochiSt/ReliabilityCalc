#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor.h"
//#include "resistor.h"

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl;

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;

    schematic* CLKdecoupling = new schematic("Clock Decoupling");

    CLKdecoupling -> addComponent(new capacitor("C1", 10*capacitor::nF, 5, 10, 85, capacitor::Q_LESS ));
    CLKdecoupling -> addComponent(new capacitor("C2", 10*capacitor::nF, 5, 10, 85, capacitor::Q_LESS ));

    component::environment = component::GF;

    cout << "###############################################################################" << endl;
    cout << endl;

    double FIT = CLKdecoupling -> getFIT();

    cout << "Total FIT " << FIT << " / " << component::FITunit << endl;

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;

    cout << "Failures within 6 years: " << schematic::getFailureRate( 6 * component::YEAR, FIT ) * 100. << " %" << endl;

    cout << endl;
    return 0;
}
