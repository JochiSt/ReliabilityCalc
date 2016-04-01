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
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl << endl;

    schematic* CLKdecoupling = new schematic("Clock Decoupling");

    component::setAmbientTemperature(55);

//   CLKdecoupling -> addComponent(new resistor("R1", 1*resistor::kOhm, 10*resistor::mW, 100*resistor::mW, resistor:: Q_S, resistor::S_RM) );
//    CLKdecoupling -> addComponent(new capacitor("C1", 15*capacitor::nF, 200+sqrt(2)*50., 400., 125 , capacitor::Q_S, capacitor::S_CQ));
    CLKdecoupling -> addComponent( new IC("U1", 1E8, 55, IC::MTTF) );

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

    schematic::printPartCount();

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;
    float testT = 120;
    cout << "Acceleration Factor for "<< testT << " degC " << CLKdecoupling -> getAccelerationFactor(testT, 40) << endl;



/*
    vector<float> v_temp, v_data;
    CLKdecoupling -> temperatureScan(10, 40, 120, v_temp, v_data);
    schematic::exportDataToFile("temp_FIT", v_temp, v_data);

    CLKdecoupling -> temperatureScanAF(10, 40, 120, v_temp, v_data);
    schematic::exportDataToFile("temp_AF", v_temp, v_data);
*/

    return 0;
}
