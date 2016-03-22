/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 FIT calculation based on MIL-HDBK-217F
 Calculation for fixed film resistors (MIL-R-22684, MIL-R-10509)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef RESISTOR_H
#define RESISTOR_H

#include "component.h"

class resistor : public component {
    public:
        static const float MOhm = 1;
        static const float kOhm = 1./1000.;
        static const float Ohm = 1./(1000*1000);

        enum Rquality_t {
            Q_S     = 3,
            Q_R     = 10,
            Q_P     = 30,
            Q_M     = 100,
            Q_MIL   = 500,
            Q_LESS  = 1500
        };

        /**
         * Resistor
         * \param value     capacity value in pF
         * \param usedPower     used voltage / applied voltage
         * \param ratedPower    rated voltage
         * \param ratedT    rated temperature
         * \param qual      part quality
         */
        resistor(std::string name, float value, float usedP, float ratedP, Rquality_t qual);
        virtual ~resistor();

        float getResistance() { return resistance; }
        void setResistance(float val) { resistance = val; }

        virtual float getFIT();

    protected:
        float resistance;
        float usedPower;
        float ratedPower;

    private:
};

#endif // RESISTOR_H
