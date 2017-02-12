#ifndef CRYSTAL_EPSON_H
#define CRYSTAL_EPSON_H

#include "crystal.h"

/**
 * @brief implementation of crystal oszillators from EPSON
 * @author Jochen Steinmann with help of Agnese Giaz
 */
class crystal_EPSON : public crystal {

    public:
	crystal_EPSON(std::string name, float basicFIT, float basicFitTemp);

	virtual ~crystal_EPSON();

    protected:

};

#endif

