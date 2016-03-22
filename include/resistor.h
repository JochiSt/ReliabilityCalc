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

        static const float mW = 1./1000.;
        static const float kW = 1000.;

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
         * \param value     capacity value in MegaOhm
         * \param usedPower used power / applied power in Watt
         * \param ratedPower rated power in Watt
         * \param ratedT    rated temperature
         * \param qual      part quality
         */
        resistor(std::string name, float value, float usedP, float ratedP, Rquality_t qual = resistor::Q_LESS);
        resistor(){ };
        virtual ~resistor();

        /**
         * @return resistance in MegaOhm
         */
        float getResistance() { return resistance; }

        /**
         * set resistance
         * @param val resistance in Mega Ohm
         */
        void setResistance(float val) { resistance = val; }

        virtual float getFIT();

        virtual std::string toString();
        virtual int fromString(std::string value);

        static std::string getIdentifier(){
            return identifier;
        }

    protected:
        float resistance;   ///< resistance
        float usedPower;    ///< used Power in W
        float ratedPower;   ///< rated Power in W

    private:
        static std::string identifier;

};

#endif // RESISTOR_H
