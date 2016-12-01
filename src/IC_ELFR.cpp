#include "IC_ELFR.h"

#include <cmath>

IC_ELFR::IC_ELFR(std::string name, float fit, float fit_temperature) : IC(name, fit, fit_temperature){
}
IC_ELFR::~IC_ELFR(){
}

float IC_ELFR::estimateWeibullExponent(float earlyLifetimeHours){
    if (ELFR > 0.){
        // std::cout << "log(-log(1. - " << ELFR << ")) / (log(" << getFIT()/1E6 << " * " << earlyLifetimeHours << ")) = " << log(-log(1. - ELFR)) / (log(getFIT()/1E6 * earlyLifetimeHours)) << std::endl;
        return log(-log(1. - ELFR)) / (log(getFIT()/1E6 * earlyLifetimeHours));
    } else {
        return -1.;
    }
}
