#ifndef SCHEMATIC_H
#define SCHEMATIC_H

#include <vector>
#include "component.h"

/**
 * A schematic consists of multiple components. Using this class, the parts can be
 * added to the schematic and when the FIT value should be calculated, the schematic
 * calculates the overall reliability.
 *
 * @brief calculate reliability of multiple components
 */
class schematic : public component {
    public:
        enum estimation_t{
            MINIMUM,
            MAXIMUM,
            MEAN,
            STDDEV
        };
	/// constructor
        schematic(std::string name);
        virtual ~schematic() { };

        /**
         * sets the ambient temperature
         * @param val ambient / operating temperature in degrees Celsius
         */
        void setAmbientTemperature(float val){
            component::setAmbientTemperature(val);
        }

        /**
         * \return ambient / operating temperature in degrees Celsius
         */
        float getAmbientTemperature(){
            return component::getAmbientTemperature();
        }

        /** @name Schematic Handling
         *  Functions needed to add and remove parts from the schematic
         */
        ///@{
        /**
         * add component to schematic
         * \param part component, which should be added
	 * \param cnt number of exactly the same components, which should be added
	 * \param critical defines, whether this part is critical for the mission or not
         */
        void addComponent(component* part, unsigned int cnt, bool critical){
            if(part != NULL){
                parts.push_back(part);
		part_count.push_back(cnt);
		part_critical.push_back(critical);
            }
        }

        void addComponent(component* part, unsigned int critical = 1){
	    if( critical == 0 || critical == 1){
		addComponent(part, 1, critical);
	    }else{
		// deprecated usage of this function
		addComponent(part, critical, true);
	    }
	}

        /**
         * get pointer to latest add component
         * @return pointer to last added component
         * @return NULL if there is no last element
         */
        component* getLastComponent(){
            if(parts.size() > 0){
                return parts.at( parts.size() - 1 );
            }else{
                return NULL;
            }
        }

        /**
         * clear parts stored in schematic
         */
        virtual void clear(){
            parts.clear();
            part_count.clear();
        };

        /**
         * remove last part, the latest part added
         */
        virtual void removeLastComponent(){
            if(!parts.empty()){
                parts.pop_back();
                part_count.pop_back();
            }
        };
        ///@}

        /**
         * calculate failures in time for this schematic
         * @return FIT value of this schematic
         */
        virtual float getFIT();

        /**
         * enable verbose output
	 * \param[in] value enables or disabled verbose output
         */
         virtual void setVerboseOutput(bool value = true){
                verbose_output = value;
         }
	 /**
	  * \return status of verbose output
	  */
         virtual bool getVerboseOutput(){
                return verbose_output;
         }


        /**
         * calculate FIT for a given temperature
         * @return FIT value at temperature
         * @param temperature temperature in deg C, at which FIT is evaluated
         * @param output defined whether output is printed or not
         */
        virtual float getFIT(float temperature, bool output = true);

/*
 *      virtual float estimateWeibullExponent(float earlyLifetimeHours=3000.);
 *      virtual float estimateWeibullExponent(float earlyLifetimeHours=3000., estimation_t type=MEAN);
*/

        /**
         * Display the part count for this schematic.
         */
        static void printPartCount();

        /**
         * convert a given FIT into a failure rate after a given number of device hours
         * @param deviceHours device hours
         * @param FIT failures in time
         * @return failure rate in 1 (to get it into percent multiply by 100)
         */
/*
        static float getFailureRate(float deviceHours, double FIT, float weibullExponent=1.);

        static float getFailureRateError(float deviceHours, double FIT, float weibullExponent=1., float weibullExponentError=0.);

*/

        /**
         * calculate acceleration factor of schematic
         * @return acceleration factor
         * @param testT test temperature (temperature, which should be used in test) in deg C
         * @param refT reference temperature (temperature, the electronics is operating) in deg C
         */
        virtual float getAccelerationFactor(float testT, float refT);

        /** @name Special Scans
         *  to evaluate the impact of various changes, e.g. the temperature special functions can be used
         */
        ///@{
        /**
         * do a temperature scan to see the effect of different temperatures on reliability
         * @param points number of points, equally distributed
         * @param startT start point of temperature
         * @param stopT stop point of temperature
         * @param temp vector with temperature points
         * @param FIT vector with FIT values at the corresponding temperatures
         */
        virtual void temperatureScan(int points, float startT, float stopT, std::vector<float> &temp, std::vector<float> &FIT);

        /**
         * do a temperature scan to see the effect of different temperatures on the accelerated aging factor
         * @param points number of points, equally distributed
         * @param startT start point of temperature
         * @param stopT stop point of temperature
         * @param temp vector with temperature points
         * @param AF vector with AF values at the corresponding temperatures
         */
        virtual void temperatureScanAF(int points, float startT, float stopT, std::vector<float> &temp, std::vector<float> &AF);
        ///@}

        /**
         * export two vectors into a tab separated output file
         * @param filename full filename of output file
         * @param vec1 first vector
         * @param vec2 second vector
         */
        static void exportDataToFile(std::string filename, std::vector<float> vec1, std::vector<float>vec2);


/*****************************************************************************
 * Failure Mode Distribution Handling
 * 
 */
	/**
	 * @brief calculate FIT based on MC (using the given probabilities)
	 * @param[in] runtime time, which is used to calculate the probabilities
	 * @param[in] tries number of MC calculations
	 */
	virtual void MCcalculateFIT(double &FITall, double &FITfmd, double runtime = 6*365*24., unsigned long int tries = 1E6);

	/**
	 * @brief set the limit of small errors, which do not cause the mission to fail
	 * @param[in] errors number of errors
	 */
	virtual void MCsetLimitSoftError(unsigned int errors){
	    MCsoftErrorTol = errors;
	}

    protected:
	/// allowed number of non mission critical errors
	unsigned int MCsoftErrorTol;

    private:
        /// store components of this schematic
        std::vector<component*> parts;

	/// store the amount of parts of the same type
        std::vector<unsigned int> part_count;

	/// store whether the component is critical for the mission
        std::vector<bool> part_critical;

        /// verbose output
        bool verbose_output;
};

#endif // SCHEMATIC_H
