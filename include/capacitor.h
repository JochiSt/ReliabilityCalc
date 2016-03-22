#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "component.h"

/**
 * @brief Implementation of reliability of capacitors
 */
class capacitor : public component {
    public:
        static const float pF = 1.;
        static const float nF = 1000.;
        static const float uF = 1000. * 1000;

        static const float V  = 1.;
        static const float mV = 1./1000.;
        static const float kV = 1000.;

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
        virtual void fromString(std::string value);

    protected:
        float capacity;     ///< capacity in pF
        float usedVoltage;  ///< voltage applied to the capacitor
        float ratedVoltage; ///< rated voltage of the capacitor

    private:
};

#endif // CAPACITOR_H
