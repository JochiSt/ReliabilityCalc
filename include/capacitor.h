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

        /** \enum capacitor::Cquality_t
         * quality of the capacitor for an exact definition have a look at the MIL HDBK
         */
        enum Cquality_t {
            Q_D     = 1,
            Q_C     = 10,
            Q_S     = 30,
            Q_R     = 100,
            Q_P     = 300,
            Q_M     = 1000,
            Q_L     = 3001,
            Q_MIL   = 3000,
            Q_LESS  = 10000
        };

        /**
         * @enum Cstyle_t Capacitor Style according to MIL-HDBK-217F Notice 2 10-1
         */
        enum Cstyle_t {
            S_CP,           ///<
            S_CA,           ///<
            S_CZ, S_CZR,    ///<
            S_CQ, S_CQR,    ///<
            S_CH,           ///<
            S_CHR,          ///<
            S_CFR,          ///<
            S_CRH,          ///<
            S_CM,           ///<
            S_CMR,          ///<
            S_CB,           ///<
            S_CY,           ///<
            S_CYR,          ///<
            S_CK,           ///< Capacitor, fixed, ceramic dielectric (General Purpose)
            S_CKR,          ///< Capacitor, fixed, ceramic dielectric (General Purpose) established reliability
            S_CC, S_CCR,    ///<
            S_CDR,          ///<
            S_CSR,          ///<
            S_CWR,          ///<
            S_CL,           ///<
            S_CLR,          ///<
            S_CRL,
            S_CU, S_CUR,    ///<
            S_CE,           ///<
            S_CV,           ///<
            S_PC,           ///<
            S_CT,           ///<
            S_CG            ///<
        };

        /**
         * Constructor of Capacitor
         * \param name      internal naming of capacitor, e.g. C1, C2
         * \param value     capacity value in pF
         * \param usedU     used voltage / applied voltage
         * \param ratedU    rated voltage
         * \param ratedT    rated temperature
         * \param qual      part quality
         * \param styl      part style
         */
        capacitor(std::string name, float value, float usedU, float ratedU, float ratedT, Cquality_t qual = capacitor::Q_LESS, Cstyle_t styl = capacitor::S_CQ);
        capacitor(){
            partcnt--;
        };
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

        static unsigned int getPartCount(){
            return partcnt;
        }

    protected:
        float capacity;     ///< capacity in pF
        float usedVoltage;  ///< voltage applied to the capacitor
        float ratedVoltage; ///< rated voltage of the capacitor
        Cquality_t quality; ///< quality of the capacitor
        Cstyle_t style;     ///< capacitor style

    private:
        static std::string identifier;
        static unsigned int partcnt;
};

#endif // CAPACITOR_H
