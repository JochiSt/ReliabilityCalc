#ifndef COMPONENT_FIT_H
#define COMPONENT_FIT_H

#include "component.h"

class component_FIT : public component {
    public:
	component_FIT(std::string name, float fit=-1);
	virtual float getFIT(){ return FIT; };

    protected:
	float FIT;
};

#endif
