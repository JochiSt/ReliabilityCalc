#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

/**
 * @brief Basic component class
 */
class component
{
    public:
        /**
         * @addtogroup NatConst Natural Constants
         * @{
         */
        static const float YEAR = 365. * 24;    ///< hours of one year
        static const float kB = 8.6173303E-5;   ///< Boltzmann constant
        static const float KELVIN = 273.15;     ///< convert Celsius into Kelvin
        ///@}

	/**
 	 * @addtogroup convUnits 
 	 * @{
 	 */
        enum Unit_t {
            FITe6   = 1,        ///< FIT value as defined in the MIL-HDBK-217
            FITe9   = 1000,     ///< FIT as defined by most other sources
            MTTF    = 1000000,  ///< Mean Time To Failure
            MTBF    = 1000000   ///< Mean Time between Failure (threated as the same)
        };
	///@}

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

        component(std::string name);
        component(){};
        virtual ~component(){ };

	/// return the ambient temperature
        static float getAmbientTemperature() {
            return ambientTemperature;
        }

	/// set ambient temperature
        static void setAmbientTemperature(float val) {
            if(val < KELVIN){
                val += KELVIN;
            }
            ambientTemperature = val;
        }

        /// pure virtual function, which should be implemented inside each sub component
        virtual float getFIT() = 0;
	
	/// estimate the Weibull Exponent, which can be used as a very preliminary estimator for the early failures
        virtual float estimateWeibullExponent(float earlyLifetimeHours=3000.);

        /**
         * put all relevant informations into one string
         */
        virtual std::string toString() {
            return name;
        }

        /**
         * return internal name of part
         */
        virtual std::string getName(){
            return name;
        }

        /**
         * set all relevant informations from one string
         */
        virtual int fromString(std::string value) {
            name = value;
            return 0;
        }

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
        static float ambientTemperature;	///< define operating temperature for all parts
        static environment_t environment;	///< operating environment
        static std::string FITunit;		///< string of FIT unit

    protected:
        float qualityFactor;			///< quality factor
        float environmentFactor;		///< environment factor
        float ratedTemperature;			///< rated temperature
        std::string name;			///< name of the component

    private:
        static std::string identifier;		///< which type of component is this
        static unsigned int partcnt;		///< total part count

};

#endif // COMPONENT_H
