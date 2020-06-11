#include "resistor_mil.h"

#include <float.h>
#include <cmath>
#include <iostream>
#include <sstream>

std::string resistor_mil::identifier = "R";
unsigned int resistor_mil::partcnt = 0;

resistor_mil::resistor_mil(std::string name, float value, float usedP, float ratedP,
                   r_style_t r_sty)
    : component(name) {
  resistance = value;
  usedPower = usedP;
  ratedPower = ratedP;

  stress = usedPower / ratedPower;

  style_factor = (float)r_sty / 10000.;
  style = r_sty;

  partcnt++;
}

resistor_mil::resistor_mil(std::string name, float value, float stre, r_style_t r_sty)
    : component(name) {
  resistance = value;
  usedPower = 0;
  ratedPower = 0;

  stress = stre;

  style_factor = (float)r_sty / 10000.;
  style = r_sty;

  partcnt++;
}

float resistor_mil::getFIT() {
  float FIT = 0;
  // Temp factor
  if (style == RC || style == RCR || style == RA || style == RK ||
      style == RQ || style == RVC)
    temp_factor =
      exp((-0.2 / 8.617e-5) * ((1. / (ambientTemperature)) - (1. / 298.)));
  else if (style == RD || style == RTH)
    temp_factor = 1.;
  else
    temp_factor =
      exp((-0.08 / 8.617e-5) * ((1. / ambientTemperature) - (1. / 298.)));

  //stress factor
  if (style == RC || style == RCR || style == RW || style == RWR || style == RE || style == RER )
    stress_factor = 0.54*pow(2.72, (2.04 * stress));
  else if (style == RZ || style == RTH)
    stress_factor = 1.;
  else
    stress_factor = 0.71*pow(2.72, (1.1 * stress));

  //power factor
  pow_factor = pow(usedPower, 0.39);

  //env_factor
  env_factor = 1.;

  //qual_factor
  qual_factor = 3.; //assumed to be non-established reliability resistors

  FIT = style_factor * temp_factor * pow_factor * stress_factor * env_factor * qual_factor;

  return FIT;

}
