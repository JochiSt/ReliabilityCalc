#include "capacitor_mil.h"

#include <float.h>
#include <cmath>

std::string capacitor_mil::identifier = "C";
unsigned int capacitor_mil::partcnt = 0;

capacitor_mil::capacitor_mil(std::string name, float value, float usedU, float ratedU,
                     style_t sty)
    : component(name) {
  capacity = value;
  usedVoltage = usedU;
  ratedVoltage = ratedU;

  stress = usedVoltage / ratedVoltage;

  // Style factor
  style_factor = (float)sty / 1000000000.;

  style = sty;

  partcnt++;
}

capacitor_mil::capacitor_mil(std::string name, float value, float stre, style_t sty)
    : component(name) {
  capacity = value;

  usedVoltage = 0;
  ratedVoltage = 0;

  stress = stre;

  // Style factor
  style_factor = (float)sty / 1000000000.;

  style = sty;

  partcnt++;
}

float capacitor_mil::getFIT() {
  float FIT = 0;
  // Temp factor
  if (style == CP || style == CA || style == CZ || style == CQ || style == CH ||
      style == CHR || style == CFR || style == CRH || style == CSR ||
      style == CWR || style == CL || style == CLR || style == CRL ||
      style == CV || style == CG)
    temp_factor = exp((-0.15 / 8.617e-5) *
                    ((1. / (ambientTemperature)) - (1. / 298.)));
  else
    temp_factor = exp((-0.35 / 8.617e-5) *
                      ((1. / (ambientTemperature)) - (1. / 298.)));

  // Cap factor
  if (style == CP || style == CA || style == CZ || style == CQ || style == CH ||
      style == CHR || style == CFR || style == CRH || style == CM ||
      style == CMR || style == CB || style == CY || style == CYR ||
      style == CK || style == CKR || style == CC || style == CDR ||
      style == CV || style == PC || style == CT || style == CG)
    cap_factor = pow((capacity / (1000. * 1000.)), 0.09);
  else
    cap_factor = pow((capacity / (1000. * 1000.)), 0.23);

  // volt factor
  if (style == CP || style == CA || style == CZ || style == CQ || style == CH ||
      style == CHR || style == CFR || style == CRH || style == CU ||
      style == CE)
    volt_factor = pow((stress / 0.6), 5) + 1;
  else if (style == CM || style == CMR || style == CB || style == CY ||
           style == CYR)
    volt_factor = pow((stress / 0.6), 10) + 1;
  else if (style == CK || style == CKR || style == CC || style == CDR)
    volt_factor = pow((stress / 0.6), 3) + 1;
  else if (style == CSR || style == CWR || style == CL || style == CLR ||
           style == CRL)
    volt_factor = pow((stress / 0.6), 17) + 1;
  else
    volt_factor = pow((stress / 0.5), 3) + 1;

  //res factor
  res_factor = 1.; //only for tantalium

  //quality factor
  qual_factor = 3.; //assumed its P

  //env factor
  env_factor = 1.; //To implement other possibilities

  FIT = style_factor * temp_factor * cap_factor * volt_factor * res_factor * qual_factor * env_factor;

  return FIT;

}

capacitor_mil::~capacitor_mil() {
  // dtor
  partcnt--;
}
