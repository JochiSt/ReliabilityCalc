#include "inductor_coilcraft.h"

inductor_coilcraft::inductor_coilcraft (std::string name, float FIT_val) : inductor(name){ 
	FIT = FIT_val;
};

inductor_coilcraft:: ~inductor_coilcraft(){
};
	
float inductor_coilcraft::getFIT(){
	return FIT;
};
	
