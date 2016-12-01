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
         * Constructor of the IC
         * @param name
         * @param fit FIT value itself
         * @param fit_temperature temperature of the given FIT
         */
        IC(std::string name, float fit=-1, float fit_temperature=-1);
        virtual ~IC();

        /// set the FIT value
        void setFIT(float val) { FIT = val; };
        /// set the temperature when there FIT value is valid
        void setFITtemperature(float val) { FIT_temperature = val; };

        virtual float getFIT();

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
