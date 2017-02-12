#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "component.h"

/**
 * @brief implementation of crystal oszillators
 * @author Jochen Steinmann with help of Agnese Giaz
 */
class crystal : public component {

    public:
	crystal(std::string name, float basicFIT, float basicFitTemp);

	virtual ~crystal();

        /// @return FIT of this specific component
        virtual float getFIT();

	/// get capacitor identifier
        static std::string getIdentifier(){
            return identifier;
        }
	/// get the capacitor part count
        static unsigned int getPartCount(){
            return partcnt;
        }

    protected:
	float EA;	///< activation energy for calculation of acceleration factor
	float BaseFit;	///< basic FIT value of the specific crystal
	float FITtemp;	///< temperature for which BaseFit is valid

    private:
        static std::string identifier;	///< store capacitor identifier
        static unsigned int partcnt;	///< static variable for counting the parts

};

#endif

