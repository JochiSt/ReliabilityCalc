#ifndef COMPONENT_MIL_HDBK_217F_H
#define COMPONENT_MIL_HDBK_217F_H

#include <string>

#include "component.h"

/**
 * @brief Basic component class
 */
class component_MIL_HDBK_217F : public component
{
    public:
        /**
         * environment definition according to MIL HDBK
         */
        enum environment_t{
            GB,     ///< Ground, Benign
            GF,     ///< Ground, Fixed
            GM,     ///< Ground, Mobile
            NS,     ///< Naval, Sheltered
            NU,     ///< Naval, Unsheltered
            AIC,    ///< Airborne, Inhabited Cargo
            AIF,    ///< Airborne, Inhabited Fighter
            AUC,    ///< Airborne, Uninhabited Cargo
            AUF,    ///< Airborne, Uninhabited Fighter
            ARW,    ///< Airborne, Rotary Winged
            SF,     ///< Space, Flight
            MF,     ///< Missile, Flight
            ML,     ///< Missile, Launch
            CL      ///< Cannon, Launch
        };

        /**
         * calculation methods
         */
        enum calc_method_t{
            MIL_HDBK_217F,          ///< using MIL Handbook 217F without notice
            MIL_HDBK_217F_NOTICE1,  ///< using MIL Handbook 217F notice 1
            MIL_HDBK_217F_NOTICE2   ///< using MIL Handbook 217F notice 2
        };

        component_MIL_HDBK_217F(std::string name);
        virtual ~component_MIL_HDBK_217F(){ };

        /**
         * @return identifier for im- and export
         */
        static std::string getIdentifier(){
            return identifier;
        }

        /**
         * @return get part count
         */
        static unsigned int getPartCount(){
            return partcnt;
        }

    public:
        static calc_method_t calculation_method;///< used calculation method
        static environment_t environment;	///< operating environment

    protected:
        float qualityFactor;			///< quality factor
        float environmentFactor;		///< environment factor
        float ratedTemperature;			///< rated temperature

    private:
        static std::string identifier;		///< which type of component is this
        static unsigned int partcnt;		///< total part count

};

#endif // COMPONENT_H
