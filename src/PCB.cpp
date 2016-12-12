#include "PCB.h"
#include <float.h>
#include <cmath>

std::string PCB::identifier = "PCB";
unsigned int PCB::partcnt = 0;

PCB::PCB(std::string name, int lay, int conn, via_technology_t tech, float minTraceW ) : component(name){
	layers = lay;
	connections = conn;
	viatech = tech;
	minTraceWidth = minTraceW;
	partcnt++;
}

PCB::~PCB(){
	partcnt--;
}

float PCB::getFIT(){
	float PCB_class = 1.;
	if( minTraceWidth < 500 && minTraceWidth >= 310 ){
		PCB_class = 2.;
	}else if( minTraceWidth < 310 && minTraceWidth >= 210 ){
		PCB_class = 3.;
	}else if( minTraceWidth < 210 && minTraceWidth >= 150 ){
		PCB_class = 4.;
	}else if( minTraceWidth < 150 && minTraceWidth >= 125 ){
		PCB_class = 5.;
	}else if( minTraceWidth < 125 && minTraceWidth >= 100 ){
		PCB_class = 6.;
	}else if( minTraceWidth < 100 ){
		PCB_class = FLT_MAX;
	}
	return 5e-4 * sqrt(layers) * ( (float) connections / 2.) * ((float)viatech / 100.) * PCB_class;
}
