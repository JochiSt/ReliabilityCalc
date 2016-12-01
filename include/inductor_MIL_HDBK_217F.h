/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 FIT calculation based on MIL-HDBK-217F
 Calculation for fixed inductive devices (MIL-C-15305, MIL-C-39010)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef INDUCTOR_MIL_HDBK_217F_H
#define INDUCTOR_MIL_HDBK_217F_H

#include "component_MIL_HDBK_217F.h"
#include "inductor.h"

class inductor_MIL_HDBK_217F : public inductor, public component_MIL_HDBK_217F {
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
        inductor_MIL_HDBK_217F(std::string name, float ratedT, Iquality_t qual = inductor_MIL_HDBK_217F::Q_LESS);
        virtual ~inductor_MIL_HDBK_217F();

        virtual float getFIT();

    protected:
        float FIT;

    private:

};

#endif // INDUCTOR_H
