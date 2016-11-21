#ifndef UTILS_H
#define UTILS_H

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
};

#endif