/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 FIT values for ICs must be provided by the manufacturer
 Correction Factor is given by the JEDEC-Standard. ONLY for Silicium based ICs!
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef IC_H
#define IC_H

#include "component.h"

class IC : public component{
    public:

        enum Unit_t {
            FITe6   = 1,    //FIT value as defined in the MIL-HDBK-217
            FITe9   = 1000,    //FIT as defined by most other sources
            MTTF    = 1000000    //mean time to failure / mean time between failure
        };

        IC(std::string name, float fit, float fit_temperature, Unit_t fit_unit);     //fit temperature is the temperature the fit-value is normalized to
        virtual~ IC();

        void setFIT(float val) { FIT = val; }

        virtual float getFIT();

    protected:
        float FIT;
        float FIT_temperature;

    private:
};

#endif // IC_H
