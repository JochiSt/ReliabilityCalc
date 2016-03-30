#ifndef DIODE_H
#define DIODE_H

#include "component.h"

/**
 * FIT calculation based on MIL-HDBK-217F
 * Calculation for low frequency diodes (metallurgically bonded) (MIL-S-19500)
 */
class diode : public component
{
    public:

        /**
         * @enum diode::quality_t quality of the diode
         */
        enum quality_t {
            Q_JANTXV    = 70,
            Q_JANTX     = 100,
            Q_JAN       = 240,
            Q_Lower     = 550,
            Q_Plastic   = 800,
        };

        /**
         * @enum diode::application_t Application of the diode, please have a look at the MIL-HDBK-217F
         */
        enum application_t {
            GENERAL_PURPOSE_ANALOG  = 38,   ///<
            SWITCHING               = 10,   ///<
            POWER_RECTIFIER         = 690,  ///<
            SCHOTTKY                = 30,   ///<
            PR_HIGH_VOLTAGE         = 50,   ///<
            TRANSIENT_SUPPRESSOR    = 13,   ///<
            CURRENT_REGULATOR       = 34,   ///<
            VOLTAGE_REGULATOR       = 20,   ///<
            VOLTAGE_REFERENCE       = 20    ///<
        };

        diode(std::string name, float usedU, float ratedU, application_t app, quality_t qual);
        diode(){};
        virtual ~diode(){};

        virtual float getFIT();

        virtual std::string toString();
        virtual int fromString(std::string value);

        static std::string getIdentifier(){
            return identifier;
        }
    protected:
        /// used voltage
        float usedVoltage;
        /// rated voltage
        float ratedVoltage;
        /// application of the diode
        application_t application;
        /// application factor for the calculation
        float applicationFactor;

    private:
        static std::string identifier;
};

#endif // DIODE_H
