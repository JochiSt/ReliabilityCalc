#ifndef ESS_H
#define ESS_H

class ESS {

    public:
	/**
	 * @brief calculate screening strength for temperature cycles
	 * 
	 * @param[in] Trange temperature range in deg Celsius
	 * @param[in] dT rate of temperature change
	 * @param[out] cycles number of cycles, which are performed
	 * @return calculated Screening Strength
	 */
	static float ScreenStrengthTC(float Trange, float dT, int cycles);


};

#endif
