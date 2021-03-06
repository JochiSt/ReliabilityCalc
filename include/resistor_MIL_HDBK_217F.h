/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 FIT calculation based on MIL-HDBK-217F
 Calculation for fixed film resistors (MIL-R-22684, MIL-R-10509)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef RESISTOR_MIL_HDBK_217F_H
#define RESISTOR_MIL_HDBK_217F_H

#include "resistor.h"
/**
 * @brief Implementation of calculation for fixed film resistors (MIL-R-22684, MIL-R-10509)
 *
 * Implementation of Notice 2 (partially) checked using
 *  http://www.sqconline.com/resistor-failure-rate-model-mil-hdbk-217-rev-f-notice-2
 */
class resistor_mil_hdbk_217F : public resistor {
    public:

        /**
         * @enum Rquality_t Quality of resistors
         */
        enum Rquality_t {
            Q_S          = 3,    ///<
            Q_R          = 10,   ///<
            Q_P          = 30,   ///<
            Q_M          = 100,  ///<
            Q_NONEST     = 300,  ///< non established reliability (Most two letter styles)
            Q_MIL        = 500,  ///<
            Q_COMMERCIAL = 1000, ///< commercial or unknown screening level
            Q_LESS       = 1500  ///<
        };

        /**
         * @enum Rstyle_t Resistor Style according to MIL-HDBK-217F Notice 2 9-1
         */
        enum Rstyle_t {
            S_RC,             ///< Resistor Fixed, Composition (insulated)
            S_RCR,            ///<
            S_RL,             ///<
            S_RLR,            ///<
            S_RNR, S_RNC, S_RNN,  ///<
            S_RM,             ///< Resistor Fixed, Film, Chip, Established Reliability
            S_RN,             ///<
            S_RD,             ///<
            S_RZ,             ///<
            S_RB,             ///<
            S_RBR,            ///<
            S_RW,             ///<
            S_RWR,            ///<
            S_RE,             ///<
            S_RER,            ///<
            S_RTH,            ///<
            S_RT,             ///<
            S_RTR,            ///<
            S_RR,             ///<
            S_RA,             ///<
            S_RK,             ///<
            S_RP,             ///<
            S_RJ,             ///<
            S_RJR,            ///<
            S_RV,             ///<
            S_RQ,             ///<
            S_RVC             ///<
        };

        /**
         * Resistor
         * \param name      part name e.g. R1
         * \param value     capacity value in MegaOhm
         * \param usedP     used power / applied power in Watt
         * \param ratedP    rated power in Watt
         * \param qual      part quality
         * \param styl      resistor style (only used in Notice 2 calculation)
         */
        resistor(std::string name, float value, float usedP, float ratedP, Rquality_t qual = resistor::Q_LESS, Rstyle_t styl = resistor::S_RL);
        resistor(std::string name, float fit_value, float fit_temperature_value, Unit_t fit_unit);
        resistor(){
            partcnt--;
        };
        virtual ~resistor() {};

        /**
         * @return resistance in MegaOhm
         */
        float getResistance() { return resistance; }

        /**
         * set resistance
         * @param val resistance in Mega Ohm
         */
        void setResistance(float val) { resistance = val; }

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
        Rstyle_t style;     ///< resistor style

        float FIT_ambient;  ///< FIT value of the resistor. Is used if FIT/MTTF/MTBF is given.
        float FIT_temperature;  ///< Corresponding test temperature of the FIT value. Corrections for higher temperatures are done with the MIL standard.

        bool FIT_given;     ///< Boolean that is set internaly, depending on which constructor is used.

    private:
        static std::string identifier;
        static unsigned int partcnt;

};

#endif // RESISTOR_H
