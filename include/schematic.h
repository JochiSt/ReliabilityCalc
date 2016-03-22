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
        virtual ~schematic();

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
            parts.push_back(part);
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

    protected:
        /// store components of this schematic
        std::vector<component* > parts;

    private:
};

#endif // SCHEMATIC_H
