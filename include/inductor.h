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
         * \param name      internal naming of inductor, e.g. C1, C2
         * \param ratedT    rated maximum Temperature
         */

        inductor(std::string name, float ratedT, Iquality_t qual);
        virtual ~inductor();

        virtual float getFIT();

    protected:

    private:
};

#endif // INDUCTOR_H
