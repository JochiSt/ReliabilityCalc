#ifndef SCHEMATIC_H
#define SCHEMATIC_H

#include <vector>

#include "component.h"

class schematic : public component {
    public:
        schematic(std::string name);
        virtual ~schematic();

        float getFIT();
        void setAmbientTemperature(float val){
            component::setAmbientTemperature(val);
        }
        float getAmbientTemperature(){
            return component::getAmbientTemperature();
        }

        /// add component to schematic
        void addComponent(component* part){
            parts.push_back(part);
        }

        static float getFailureRate(float deviceHours, double FIT);

    protected:
        std::vector<component* > parts;

    private:
};

#endif // SCHEMATIC_H
