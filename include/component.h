#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

/**
 * @brief Basic component class
 */
class component
{
    public:
        static const float YEAR = 365. * 24;

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

        component(std::string name);
        virtual ~component();

        static float getAmbientTemperature() {
            return ambientTemperature;
        }
        static void setAmbientTemperature(float val) {
            ambientTemperature = val;
        }

        /// pure virtual function, which should be implemented inside each sub component
        virtual float getFIT() = 0;

    public:
        static float ambientTemperature;    ///< define operating temperature for all parts
        static environment_t environment;   ///< operating environment
        static std::string FITunit;

    protected:
        float qualityFactor;                ///< quality factor
        float environmentFactor;            ///< environment factor
        float ratedTemperature;             ///< rated temperature
        std::string name;

    private:
};

#endif // COMPONENT_H
