/* 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  FIT calculation useful for VISHAY CRCWe3 resistors
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef RESISTOR_VISHAY_CRCRE3_H
#define RESISTOR_VISHAY_CRCRE3_H

class resistor_VISHAY_CRCWe3 : public resistor {
	public:
        	virtual resistor(std::string name);

		virtual float getFIT() { return 0.1; }

};

#endif
