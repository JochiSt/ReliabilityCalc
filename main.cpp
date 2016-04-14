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

    //schematic* CLKdecoupling = new schematic("Clock Decoupling");

    ///Resistor Quality
    resistor::Rquality_t Rqual = resistor::Q_MIL;

    ///Capacitor Quality
    capacitor::Cquality_t Cqual = capacitor::Q_MIL;

    ///Inductor Quality
    inductor::Iquality_t Iqual = inductor::Q_MIL;

    component::setAmbientTemperature(40);



    schematic* example = new schematic("JUNO Example Board");

    ///Example for a Capacitor implemented for MIL-HDBK-Calculation. Last Value is only needed for notice 2. For notice 1 ceramic general purpose capacitors are assumed.
    example -> addComponent(new capacitor("C1", 1*capacitor::uF, 24, 250, 125, Cqual, capacitor::S_CQ));
    ///Example for a resistor implemented for MIL-HDBK-Calculation. Last value is only needed for notice 2. For notice 1fixed film resistors are assumed.
    example -> addComponent(new resistor("R1", 1*resistor::MOhm, 1.6e-5, 0.1, Rqual, resistor::S_RM));
    ///Example for an inductor implemented for MIL-HDBK-Calculation. Inductor not jet implemented for notice 2.
    example -> addComponent(new inductor("L1", 1.1,inductor::FITe9));
    ///Example for a diode implemented for MIL-HDBK-Calculation. Diode not jet implemented for notice 2.
    example -> addComponent(new diode("D1", 3, 10, diode::GENERAL_PURPOSE_ANALOG, diode::Q_Plastic));


    ///Example for a Board with components were the producer provides reliability data
    schematic* example2 = new schematic("JUNO Exmaple Board 2");
    ///Example for a IC
    example2 -> addComponent(new IC("LT8614", 6.498e8, 55,IC::MTTF));
    ///Example for a Capacitor with given FIT value. (E.g. WE)
    example2 -> addComponent(new capacitor("C2", 0.04, 40, 0.07, 120, capacitor::FITe9));
    ///Example for a resistor with given FIT value (E.g. vishay)
    example2 -> addComponent(new resistor("R2", 0.1, 40, resistor::FITe9));
    ///Example for a inductor with given FIT value. (E.g. WE)
    example -> addComponent(new inductor("L2", 1.1,inductor::FITe9));

    ///Complete Board. Schematics of different parts can be added up to a main board

    schematic* example_board = new schematic("Complete Board");

    cout << "###############################################################################" << endl;
    cout << endl;
    ///Enviroment:
    component::environment = component::GF;

    double FIT = example_board -> getFIT();
    cout << "Fit with Notice 1 HDBK:" << endl;
    cout << "Total FIT " << FIT << " / " << component::FITunit << endl;
    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;
    ///Change from notice 1 to notice 2
    component::calculation_method = component::MIL_HDBK_217F_NOTICE2;
    FIT = example -> getFIT();
    cout << "Fit with Notice 2 HDBK:" << endl;
    cout << "Total FIT " << FIT << " / " << component::FITunit << endl;

    cout << endl;

    schematic::printPartCount();

    cout << endl;
    cout << "###############################################################################" << endl;
    cout << endl;
    float testT = 120;
    //cout << "Acceleration Factor for "<< testT << " degC " << CLKdecoupling -> getAccelerationFactor(testT, 40) << endl;



/*
    vector<float> v_temp, v_data;
    CLKdecoupling -> temperatureScan(10, 40, 120, v_temp, v_data);
    schematic::exportDataToFile("temp_FIT", v_temp, v_data);

    CLKdecoupling -> temperatureScanAF(10, 40, 120, v_temp, v_data);
    schematic::exportDataToFile("temp_AF", v_temp, v_data);
*/

    return 0;
}
