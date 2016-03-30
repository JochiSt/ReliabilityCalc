/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 FIT calculation based on MIL-HDBK-217F
 Calculation for fixed film resistors (MIL-R-22684, MIL-R-10509)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef RESISTOR_H
#define RESISTOR_H

#include "component.h"
/**
 * @brief Implementation of calculation for fixed film resistors (MIL-R-22684, MIL-R-10509)
 */
class resistor : public component {
    public:
        /**
         * @ingroup convUnits
         * @{
         */
        static const float MOhm = 1;
        static const float kOhm = 1./1000.;
        static const float Ohm = 1./(1000*1000);

        static const float mW = 1./1000.;
        static const float W = 1.;
        static const float kW = 1000.;
        ///@}

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
            RC,             ///< Resistor Fixed, Composition (insulated)
            RCR,            ///<
            RL,             ///<
            RLR,            ///<
            RNR, RNC, RNN,  ///<
            RM,             ///< Resistor Fixed, Film, Chip, Established Reliability
            RN,             ///<
            RD,             ///<
            RZ,             ///<
            RB,             ///<
            RBR,            ///<
            RW,             ///<
            RWR,            ///<
            RE,             ///<
            RER,            ///<
            RTH,            ///<
            RT,             ///<
            RTR,            ///<
            RR,             ///<
            RA,             ///<
            RK,             ///<
            RP,             ///<
            RJ,             ///<
            RJR,            ///<
            RV,             ///<
            RQ,             ///<
            RVC             ///<
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
 //       resistor(std::string name, float value, float usedP, float ratedP, Rquality_t qual = resistor::Q_LESS);
        resistor(std::string name, float value, float usedP, float ratedP, Rquality_t qual = resistor::Q_LESS, Rstyle_t styl = resistor::RC);
        resistor(){ };
        virtual ~resistor();

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

    protected:
        float resistance;   ///< resistance
        float usedPower;    ///< used Power in W
        float ratedPower;   ///< rated Power in W

        Rstyle_t style;     ///< resistor style

    private:
        static std::string identifier;

};

#endif // RESISTOR_H
