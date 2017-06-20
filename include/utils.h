#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "schematic.h"

/**
 * \class utils
 * \author Jochen Steinmann
 * \version 0.2
 * \date 2016-12-06
 * \brief collection of various functions
 *
 * Collection of multiple functions, which extend the functionality of
 * this framework. These functions can convert different numbers, 
 * calculate various values etc.
 */
class utils {

	public:
		/**
		 * \brief converts a FIT value into a failure rate in a given time
		 * \return failure rate
		 * \param[in] FIT calculated failures in time per 1E9/h
		 * \param[in] time time, which should be considered when 
		 *            calculating the failure rate
		 */
		static float FIT2FailureRate(float FIT, float time);

		/**
		 * \brief converts a given failure rate in a given time into the 
		 *        right FIT value
		 * \return FIT value
		 * \param[in] failureRate given in units of 1
		 * \param[in] deviceHours runtime of the device in hours
		 */
		static float FailureRate2FIT(float failureRate, float deviceHours);


		/**
		 * \brief calculate FIT from failures and runtime
		 * \return FIT value
		 * \param[in] conflevel confidence level typ. 0.6
		 * \param[in] failures number of observed failures
		 * \param[in] devhours device hours = runtime * devices * acceleration factor
		 */
		static float calcFIT(float conflevel, int failures, double devhours);

    /**
     * @param[in] schematic schematic, wich should be used for the temperature scan
     * @param[in] temperatures given set of temperatures
     * @param[out] FIT calculated FIT values corresponding the temperatures
     */
    static void temperatureScan(schematic* schematic, std::vector<float> temperatures, std::vector<float> &FIT);
};

#endif
