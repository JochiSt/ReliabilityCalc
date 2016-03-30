#ifndef SCHEMATIC_H
#define SCHEMATIC_H

#include <vector>

#include "component.h"

/**
 * schematic consists of multiple parts of various kind
 *
 * @brief calculate reliability of multiple components
 */
class schematic : public component {
    public:
        schematic(std::string name);
        virtual ~schematic() { };

        /**
         * calculate failures in time for this schematic
         * @return FIT value of this schematic
         */
        virtual float getFIT();

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
         * convert a given FIT into a failure rate after a given number of device hours
         * @param deviceHours device hours
         * @param FIT failures in time
         * @return failure rate in 1 (to get it into percent multiply by 100)
         */
        static float getFailureRate(float deviceHours, double FIT);

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

        /**
         * calculate acceleration factor of schematic
         * @return acceleration factor
         * @param testT test temperature (temperature, which should be used in test)
         * @param refT reference temperature (temperature, the electronics is operating)
         */
        virtual float getAccelerationFactor(float testT, float refT);

        /**
         * calculate FIT for a given temperature
         * @return FIT value at temperature
         * @param temperature temperature, at which FIT is evaluated
         */
        virtual float getFIT(float temperature){
            float tempT = getAmbientTemperature();
            float FIT = getFIT();
            setAmbientTemperature(tempT);
            return FIT;
        }

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
         * export two vectors into a tab separated output file
         * @param filename full filename of output file
         * @param vec1 first vector
         * @param vec2 second vector
         */
        virtual void exportDataToFile(std::string filename, std::vector<float> vec1, std::vector<float>vec2);

    protected:

    private:
        /// store components of this schematic
        std::vector<component*> parts;
};

#endif // SCHEMATIC_H
