#ifndef RESISTOR_H
#define RESISTOR_H

#include "component.h"
/**
 * @brief Implementation of calculation for resistors
 */
class resistor : public component {
    public:
        /**
         * @ingroup convUnits
         * @{
         */
        static constexpr float MOhm = 1;
        static constexpr float kOhm = 1./1000.;
        static constexpr float Ohm = 1./(1000*1000);

        static constexpr float mW = 1./1000.;
        static constexpr float W = 1.;
        static constexpr float kW = 1000.;
        ///@}

        /**
         * Resistor
         * \param name      part name e.g. R1
         * \param value     capacity value in MegaOhm
         * \param usedP     used power / applied power in Watt
         * \param ratedP    rated power in Watt
         */
        resistor(std::string name, float value, float usedP, float ratedP);
        resistor(std::string name, float value, float stress);
        resistor(){
            partcnt--;
        };
        virtual ~resistor() {};

        /**
         * @return resistance in MegaOhm
         */
        virtual float getResistance() { return resistance; }

        /**
         * set resistance
         * @param val resistance in Mega Ohm
         */
        virtual void setResistance(float val) { resistance = val; }

        /**
         * @brief calculate the FIT value for this component
         */
        virtual float getFIT() = 0;

        /// return the identifier
        static std::string getIdentifier(){
            return identifier;
        }

        /// get the part count
        static unsigned int getPartCount(){
            return partcnt;
        }

    protected:
        float resistance;   ///< resistance
        float usedPower;    ///< used Power in W
        float ratedPower;   ///< rated Power in W
    
	float stress;	    ///< used stress

    private:
        static std::string identifier;
        static unsigned int partcnt;

};

#endif // RESISTOR_H
