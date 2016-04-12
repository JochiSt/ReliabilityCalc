#ifndef DIODE_H
#define DIODE_H

#include "component.h"
/**
 * @brief Implementation of calculation for low frequency diodes (metallurgically bonded) (MIL-S-19500)
 *
 * FIT calculation based on MIL-HDBK-217F
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
            GENERAL_PURPOSE_ANALOG  = 38,   ///< Type: General Purpose Analog
            SWITCHING               = 10,   ///< Type: Switching
            POWER_RECTIFIER         = 690,  ///< Type: Power Rectifier, Fast Recovery
            SCHOTTKY                = 30,   ///< Type/Application: Power Rectifier/ Schottky Power Diode
            PR_HIGH_VOLTAGE         = 50,   ///< Type: Power Rectifier with High Voltage Stacks
            TRANSIENT_SUPPRESSOR    = 13,   ///< Application: Transient Suppressor, Varistor
            CURRENT_REGULATOR       = 34,   ///< Application: Current Regulator
            VOLTAGE_REGULATOR       = 20,   ///< Application: Voltage Regulator (Avalanche and Zener)
            VOLTAGE_REFERENCE       = 20    ///< Application: Voltage Reference (Avalanche and Zener)
        };

        diode(std::string name, float usedU, float ratedU, application_t app, quality_t qual);
        diode(){
            partcnt--;
        };
        virtual ~diode(){};

        virtual float getFIT();

        virtual std::string toString();
        virtual int fromString(std::string value);

        static std::string getIdentifier(){
            return identifier;
        }
        static unsigned int getPartCount(){
            return partcnt;
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
        static unsigned int partcnt;
};

#endif // DIODE_H
