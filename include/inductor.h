/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 FIT calculation based on MIL-HDBK-217F
 Calculation for fixed inductive devices (MIL-C-15305, MIL-C-39010)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "component.h"

class inductor : public component
{
    public:

        enum Iquality_t {
            Q_S     = 3,
            Q_R     = 10,
            Q_P     = 30,
            Q_M     = 100,
            Q_MIL   = 400,
            Q_LESS  = 2000
        };

        /**
         * Constructor of Inductor
         * \param name      internal naming of inductor, e.g. L1, L2
         * \param ratedT    rated maximum Temperature
         * \param qual      quality of inductor
         */
        inductor(std::string name, float ratedT, Iquality_t qual = inductor::Q_LESS);
        inductor(){ };
        virtual ~inductor(){ };

        virtual float getFIT();

        virtual std::string toString();
        virtual int fromString(std::string value);

        static std::string getIdentifier(){
            return identifier;
        }
    protected:

    private:
        static std::string identifier;
};

#endif // INDUCTOR_H
