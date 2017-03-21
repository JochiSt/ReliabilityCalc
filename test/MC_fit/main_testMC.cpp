#include <iostream>

using namespace std;

#include "schematic.h"
#include "component.h"
#include "component_FIT.h"
#include "capacitor.h"
#include "resistor.h"
#include "IC.h"
#include "inductor.h"
#include "diode.h"
#include "crystal.h"

#include "capacitor_WUERTH.h"
#include "inductor_WUERTH.h"
#include "IC_TI.h"
#include "IC_MAXIM.h"
#include "IC_AD.h"
#include "PCB.h"

#include "capacitor_WIMA.h"
#include "capacitor_WIMA_SMD_PPS.h"
#include "capacitor_VISHAY.h"

#include "crystal_EPSON.h"

#include "utils.h"

#include <cstdlib>
#include <time.h>
#include <fstream>

int main(){
    cout << "Reliability Calculator" << endl;
    cout << "\tcompiled @ " << __DATE__ << " " << __TIME__ << " using GCC " << __VERSION__ << endl << endl;

    cout << "FIT for 0.5% in 6 years " << utils::FailureRate2FIT(0.5/100., 6*365*24.) << endl;

    component::setAmbientTemperature(40);

    schematic* example = new schematic("Example Board");
    example -> addComponent( new component_FIT("T1", 100), 1, false );
    example -> addComponent( new component_FIT("T2", 100), 1, false );

    example -> MCcalculateFIT();

    example -> setVerboseOutput(true);
    float FIT = example -> getFIT();

    srand (time(NULL));
    const float fit = 100;
    
    std::ofstream outp;
    outp.open("test_distri.dat");    

    double cntAll = 0, cntFMD = 0, cnt = 0;

    float runtime = 6;
    float singleFIT = 0.03;
    for(unsigned int tries = 0; tries < 1E8; tries ++){

        int failureCounter = 0;	    // count all failures
        bool failed = false;	    // has this device failed
	bool strongfail = false;    // is this a failure, which causes the misssion to fail

        float failureProb = utils::FIT2FailureRate(singleFIT, runtime*365*24.);    
        float realFailure = 0.1;	// 50% are real failures
					// rest are failures, which do not harm that much

        for(int components=0; components<5; components++){
	    // generate the failure probability between 0 and 1
	    double componentFailure = rand();
		   componentFailure /= RAND_MAX;

            if( componentFailure < failureProb ){	// if component is failing
		    strongfail = true;
		    // generate the failure mode probability between 0 and 1
		    double failureMode = rand();
			   failureMode /= RAND_MAX;
		    if( realFailure > failureMode){		// component seriously failed
			failed = true;
		    }else{
			failureCounter ++;
		    }
	    }
        }
	cntAll ++;
	if(strongfail){
		cnt++;
		if( failureCounter > 1 || failed) {	// more than one small issue
		    cntFMD ++;
		}
	}
    }
    
    cout << cntAll << "\t" << cnt << "\t" << cntFMD << endl;

    cntFMD /= cntAll;
    cnt    /= cntAll;

    cout << cntAll << "\t" << cnt << "\t" << cntFMD << endl;

    cout << "FIT of single device: " << singleFIT << endl;
    cout << "ALL: " << utils::FailureRate2FIT(cnt, runtime * 365*24.) << endl;
    cout << "FMD: " << utils::FailureRate2FIT(cntFMD, runtime * 365*24.) << endl;

    return 0;
}
