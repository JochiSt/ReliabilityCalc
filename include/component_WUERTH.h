/**
 * http://www.we-online.com/web/en/index.php/show/media/07_electronic_components/download_center_1/technische_dokumente/WES_FIT_Nov16.pdf
 */

#ifndef COMPONENT_WUERTH_H
#define COMPONENT_WUERTH_H

#include "sqlite3_handler.h"

#include <stdio.h>
#include <stdlib.h>

class component_WUERTH {
	public:
		component_WUERTH(std::string code);

	private:
		static sqlite3_handler db;

	protected:
		void searchTable();		///< lookup matchcode
		std::string matchcode;	///< Wuerth MatchCode to select right reliability data (e.g. WE-CBA)
		std::string FIT_table;	///< FIT value table (e.g. 5.1)
		char FIT_curve;			///< FIT value curve in table (e.g. C)
								///< for capacitors, this is 30% stress level

		std::string SIGMA_table;///< FIT sigma value table (e.g. C.1)
		char SIGMA_curve;		///< FIT sigma value curve in table (e.g. n)
								///< for capacitors, this is 30% stress level

	public:
		virtual void getFIT(float temperature, float &retTempL, float &FITL, float &retTempU, float &FITU, char curve = '-');
		virtual void getSIGMA(float temperature, float &retTempL, float &SIGMAL, float &retTempU, float &SIGMAU, char curve = '-');


};
#endif
