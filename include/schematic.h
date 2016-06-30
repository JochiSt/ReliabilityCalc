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
         */
        void addComponent(component* part){
            if(part != NULL){
                parts.push_back(part);
            }
        }

        /**
         * get pointer to latest add component
         * @return pointer to last added component
         * @return NULL if there is no last element
         */
        component* lastAddedComponent(){
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
        };

        /**
         * remove last part, the latest part added
         */
        virtual void removeLastComponent(){
            if(!parts.empty()){
                parts.pop_back();
            }
        };
        ///@}

        /**
         * @name Schematic Import and Export
         * Schematics can be exported into a plain text file and they can also be imported
         */
        ///@{
        /**
         * export schematic into file
         * @param filename path and filename of file, into which should be exported
         */
        virtual void exportToFile(std::string filename);

        /**
         * import schematic from file
         * @param filename path and filename of file, which should be imported
         */
        virtual void importFromFile(std::string filename);
        ///@}

        /**
         * calculate failures in time for this schematic
         * @return FIT value of this schematic
         */
        virtual float getFIT(bool output);

        virtual float getFIT(){
            return getFIT(true);
        };


        /**
         * calculate FIT for a given temperature
         * @return FIT value at temperature
         * @param temperature temperature in deg C, at which FIT is evaluated
         * @param output defined whether output is printed or not
         */
        virtual float getFIT(float temperature, bool output = true);

        virtual float estimateWeibullExponent(float earlyLifetimeHours=3000.);
        virtual float estimateWeibullExponent(float earlyLifetimeHours=3000., estimation_t type=MEAN);

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
        static float getFailureRate(float deviceHours, double FIT, float weibullExponent=1.);

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
    protected:

    private:
        /// store components of this schematic
        std::vector<component*> parts;
};

#endif // SCHEMATIC_H
