#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

/**
 * \class component
 * \brief Basic component class
 * \author Jochen Steinmann
 * \version 1.0
 * 
 * Basic class for reliability calculation
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

        /**
	 * set ambient temperature
	 * \param[in] val temperature (if temperature is smaller than 273.15, 
	 * the temperature is automatically converted into Kelvin
	 */
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

	/**
	 * @return device temperature
	 */
	virtual float getDeviceTemperature() {
		if( deviceTemperature <= ambientTemperature ){
			return ambientTemperature;
		}else{
			return deviceTemperature;
		}
	}
	/** 
	 * sets individual device temperature
	 */
	virtual void setDeviceTemperature( float temp ){
		if( temp < KELVIN){
			temp += KELVIN;
		}
		deviceTemperature = temp;
	}

    public:
        static float ambientTemperature;	///< define operating temperature for all parts
        static std::string FITunit;		///< string of FIT unit

    protected:
        std::string name;			///< name of the component
	float deviceTemperature;		///< individual device temperature

    private:
        static std::string identifier;		///< which type of component is this
        static unsigned int partcnt;		///< total part count

};

#endif // COMPONENT_H
