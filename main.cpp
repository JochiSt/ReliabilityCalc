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

    schematic* CLKdecoupling = new schematic("Clock Decoupling");
    CLKdecoupling -> addComponent(new resistor("R1", 1*resistor::kOhm, 10*resistor::mW, 100*resistor::mW, resistor::Q_M, resistor::S_RM) );
    CLKdecoupling -> addComponent(new capacitor("C1", 15*capacitor::nF, 200+sqrt(2)*50., 400., 85 , capacitor::Q_MIL, capacitor::S_CQ));


    cout << "###############################################################################" << endl;
    cout << endl;
    component::environment = component::GF;
    double FIT = CLKdecoupling -> getFIT();
    cout << "Total FIT " << FIT << " / " << component::FITunit << endl;
    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;
    component::environment = component::GF;
    component::calculation_method = component::MIL_HDBK_217F_NOTICE2;
    FIT = CLKdecoupling -> getFIT();
    cout << "Total FIT " << FIT << " / " << component::FITunit << endl;
    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;



    return 0;
}
