#ifndef IC_H
#define IC_H

#include "component.h"

/**
 * @brief calculate the FIT of ICs
 * FIT values for ICs must be provided by the manufacturer
 * Correction Factor is given by the JEDEC-Standard. ONLY for Silicon based ICs!
 */
class IC : public component{
    public:
        /**
         * @addtogroup NatConst Natural Constants
         * @{
         */
        static const float EA = 0.7;        ///< binding energy electron in Silicium = 0.7eV
        ///@}

        /**
         * @enum Unit_t Units of FIT / MTTF value of ICs
         */
        enum Unit_t {
            FITe6   = 1,        ///< FIT value as defined in the MIL-HDBK-217
            FITe9   = 1000,     ///< FIT as defined by most other sources
            MTTF    = 1000000   ///< Mean Time To Failure
        };

        /**
         * Constructor of the IC
         * @param name
         * @param fit FIT value itself
         * @param fit_temperature temperature of the given FIT
         * @param fit_unit  Unit of the given FIT
         */
        IC(std::string name, float fit, float fit_temperature, Unit_t fit_unit);
        IC(){
            partcnt--;
        };

        /// set the FIT value
        void setFIT(float val) { FIT = val; }

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
        /// given FIT value
        float FIT;
        /// temperature the FIT value is valid
        float FIT_temperature;

    private:
        static std::string identifier;
        static unsigned int partcnt;
};

#endif // IC_H
