/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 FIT calculation based on MIL-HDBK-217F
 Calculation for fixed, ceramic general purpose capacitors (MIL-C-11015, MIL-C-39014)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "component.h"

/**
 * @brief Implementation of reliability of capacitors
 */
class capacitor : public component {
    public:
        /**
         * @addtogroup conv convenience definitions of units
         * @{
         */
        static const float pF = 1.;
        static const float nF = 1000.;
        static const float uF = 1000. * 1000;

        static const float V  = 1.;
        static const float mV = 1./1000.;
        static const float kV = 1000.;
        /**
         * }@
         */

        /** \enum capacitor::Cquality_t
         * quality of the capacitor for an exact definition have a look at the MIL HDBK
         */
        enum Cquality_t {
            Q_S     = 3,
            Q_R     = 10,
            Q_P     = 30,
            Q_M     = 100,
            Q_L     = 300,
            Q_MIL   = 300,
            Q_LESS  = 1000
        };

        /**
         * Constructor of Capacitor
         * \param name      internal naming of capacitor, e.g. C1, C2
         * \param value     capacity value in pF
         * \param usedU     used voltage / applied voltage
         * \param ratedU    rated voltage
         * \param ratedT    rated temperature
         * \param qual      part quality
         */
        capacitor(std::string name, float value, float usedU, float ratedU, float ratedT, Cquality_t qual = capacitor::Q_LESS);
        capacitor(){};
        virtual ~capacitor();

        /// @return capacity in pF
        float getCapacity() { return capacity; }
        /**
         * @param val capacity in pF
         */
        void setCapacity(float val) { capacity = val; }

        /// @return FIT of this specific component
        virtual float getFIT();

        virtual std::string toString();
        virtual int fromString(std::string value);

        static std::string getIdentifier(){
            return identifier;
        }

    protected:
        float capacity;     ///< capacity in pF
        float usedVoltage;  ///< voltage applied to the capacitor
        float ratedVoltage; ///< rated voltage of the capacitor

    private:
        static std::string identifier;
};

#endif // CAPACITOR_H
