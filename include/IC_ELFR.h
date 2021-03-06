#ifndef IC_ELFR_H
#define IC_ELFR_H

#include "IC.h"

/**
 * @brief calculate the FIT of ICs and estimate a early failure component
 */
class IC_ELFR : public IC{
    public:
        /**
         * Constructor of the IC
         * @param name
         * @param fit FIT value itself
         * @param fit_temperature temperature of the given FIT
         */
        IC_ELFR(std::string name, float fit=-1, float fit_temperature=-1);
        virtual ~IC_ELFR();

        virtual float estimateWeibullExponent(float earlyLifetimeHours=3000.);

    protected:
        /// Early failures of the IC in ppm
        float ELFR;

    private:

};

#endif // IC_H
