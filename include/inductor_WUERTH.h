#ifndef INDUCTOR_WUERTH_H
#define INDUCTOR_WUERTH_H

#include "inductor.h"


/**
 * \brief Inductors based on WÜRTH reliability data
 */
class inductor_wuerth : public inductor
{
    public:
        inductor(std::string name, float fit_value, Unit_t fit_unit);
};

#endif // INDUCTOR_H
