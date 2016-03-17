#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "capacitor.h"
//#include "resistor.h"

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl;

    schematic* CLKdecoupling = new schematic("Clock Decoupling");

    CLKdecoupling -> addComponent(new capacitor("C1", 10*capacitor::nF, 5, 10, 85, capacitor::Q_S));

    component::environment = component::GF;

    cout << CLKdecoupling -> getFIT() << endl;
    cout << CLKdecoupling -> getFailureRate(6 * component::YEAR ) << endl;

    return 0;
}
