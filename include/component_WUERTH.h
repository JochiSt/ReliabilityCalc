#ifndef COMPONENT_WUERTH_H
#define COMPONENT_WUERTH_H

#include "sqlite3_handler.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * \class component_WUERTH
 * \brief Implementation of the reliability variables for WUERTH components
 * \author Jochen Steinmann
 * \version 1.0
 * \date 2016-12-05
 * \pre get database with reliability data from WÜRTH
 *
 * Tools for getting the reliability data from the database, which is used 
 * to store the reliability data from WÜRTH, which is available at 
 * http://www.we-online.com/web/en/index.php/show/media/07_electronic_components/download_center_1/technische_dokumente/WES_FIT_Nov16.pdf
 *
 */
class component_WUERTH {
	public:
		component_WUERTH(std::string code);
		virtual ~component_WUERTH();

	private:
		/// Handler for the SQLite3 database connection
		static sqlite3_handler db;

	protected:
		void searchTable();	///< lookup matchcode
		std::string matchcode;	///< Wuerth MatchCode to select right reliability data (e.g. WE-CBA)
		std::string FIT_table;	///< FIT value table (e.g. 5.1)
		char FIT_curve;		///< FIT value curve in table (e.g. C)
					///< for capacitors, this is 30% stress level

		std::string SIGMA_table;///< FIT sigma value table (e.g. C.1)
		char SIGMA_curve;	///< FIT sigma value curve in table (e.g. n)
					///< for capacitors, this is 30% stress level

	public:
		/** 
		 * lookup the FIT value at a given temperature
 		 * \param[in] temperature	operating temperature
 		 * \param[out] retTempL		temperature lower / equal the operating 
 		 * \param[out] FITL		FIT value at see #retTempL
 		 * \param[out] retTempU		temperature higher / equal the operating temperature
 		 * \param[out] FITU		FIT value at see #retTempU
 		 *
 		 * retTempL and retTempU together with FITL and FITU can be used for linear interpolation
 		 */
		virtual void getFIT(float temperature, float &retTempL, float &FITL, float &retTempU, float &FITU, char curve = '-');
		/**
 		 * same as \see getFIT but just for the sigma value, which can be used to calculate a different confidence interval
 		 */ 
		virtual void getSIGMA(float temperature, float &retTempL, float &SIGMAL, float &retTempU, float &SIGMAU, char curve = '-');


};
#endif
