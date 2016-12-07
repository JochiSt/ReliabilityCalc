#ifndef INDUCTOR_coilcfraft_H
#define INDUCTOR_coilcfraft_H

#include "inductor.h"

class inductor_coilcraft : public inductor {

	public:
	inductor_coilcraft (std::string name, float fit_value);

	virtual ~inductor_coilcraft();
	
        virtual float getFIT();
	
	protected:
	float FIT;
	
};
#endif
