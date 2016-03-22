/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 FIT calculation based on MIL-HDBK-217F
 Calculation for low frequency diodes (metallurgically bonded) (MIL-S-19500)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef DIODE_H
#define DIODE_H

#include "component.h"

class diode : public component
{
    public:

        enum Dquality_t {
            Q_JANTXV    = 70,
            Q_JANTX     = 100,
            Q_JAN       = 240,
            Q_Lower     = 550,
            Q_Plastic   = 800,
        };

        enum Application {
            GeneralPurposeAnalog    = 38,
            Switching               = 10,
            PowerRectifier          = 690,
            Schottky                = 30,
            PR_HighVoltage          = 50,        //Please have a look into the MIL-HDBK-217F
            TransientSuppressor     = 13,
            CurrentRegulator        = 34,
            VoltageRegulator        = 20,
            VoltageReference        = 20
        };
        diode(std::string name, float ratedU, float usedU, Application app, Dquality_t qual);
        virtual ~diode();

        virtual float getFIT();

    protected:
        float usedVoltage;
        float ratedVoltage;
        float applicationFactor;
    private:
};

#endif // DIODE_H
