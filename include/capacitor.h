#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "component.h"

class capacitor : public component {
    public:
        static const float pF = 1;
        static const float nF = 1000 * 1000;
        static const float uF = 1000 * 1000 * 1000;

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
         * Capacitor
         * \param value     capacity value in pF
         * \param usedU     used voltage / applied voltage
         * \param ratedU    rated voltage
         * \param ratedT    rated temperature
         * \param qual      part quality
         */
        capacitor(std::string name, float value, float usedU, float ratedU, float ratedT, Cquality_t qual);
        virtual ~capacitor();

        float getCapacity() { return capacity; }
        void setCapacity(float val) { capacity = val; }

        virtual float getFIT();

    protected:
        float capacity;
        float usedVoltage;
        float ratedVoltage;

    private:
};

#endif // CAPACITOR_H
