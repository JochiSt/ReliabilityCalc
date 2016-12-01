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

        /**
         * return internal name of part
         */
        virtual std::string getName(){
            return name;
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
        static float ambientTemperature;	///< define operating temperature for all parts
        static std::string FITunit;		///< string of FIT unit

    protected:
        std::string name;			///< name of the component

    private:
        static std::string identifier;		///< which type of component is this
        static unsigned int partcnt;		///< total part count

};

#endif // COMPONENT_H
