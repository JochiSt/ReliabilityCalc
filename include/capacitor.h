#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "component.h"

/**
 * @brief Implementation of reliability of capacitors
 */
class capacitor : public component {
    public:
        /**
         * @addtogroup convUnits convenience definitions of units
         * @{
         */
        static const float pF = 1.;
        static const float nF = 1000.;
        static const float uF = 1000. * 1000.;

        static const float V  = 1.;
        static const float mV = 1./1000.;
        static const float kV = 1000.;
        ///@}

        /**
         * Constructor of Capacitor
         * \param name      internal naming of capacitor, e.g. C1, C2
         * \param value     capacity value in pF
         * \param usedU     used voltage / applied voltage
         * \param ratedU    rated voltage
         */
        capacitor(std::string name, float value, float usedU, float ratedU);

        virtual ~capacitor();

        /// @return capacity in pF
        float getCapacity() { return capacity; }
        /**
         * @param val capacity in pF
         */
        void setCapacity(float val) { capacity = val; }

        /// @return FIT of this specific component
        virtual float getFIT()=0;

	/// get capacitor identifier
        static std::string getIdentifier(){
            return identifier;
        }
	/// get the capacitor part count
        static unsigned int getPartCount(){
            return partcnt;
        }

    protected:
        float capacity;     ///< capacity in pF
        float usedVoltage;  ///< voltage applied to the capacitor
        float ratedVoltage; ///< rated voltage of the capacitor

    private:
        static std::string identifier;	///< store capacitor identifier
        static unsigned int partcnt;	///< static variable for counting the parts
};

#endif // CAPACITOR_H
