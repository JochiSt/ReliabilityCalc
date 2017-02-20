#ifndef IC_TI_H
#define IC_TI_H

#include "IC_DB.h"
#include <string.h>
#include <vector>
#include <curl/curl.h>

#include "sqlite3_handler.h"

/**
 * @brief calculate the FIT of TI ICs
 * FIT value is looked up from Webpage
 */
class IC_TI : public IC_DB {
    public:
        /**
         * Constructor of the IC
         * \param[in] name
         * \param[in] type correct naming of the IC (e.g. DS30EA101SQ/NOPB)
         */
        IC_TI(std::string name, std::string type);
        virtual ~IC_TI();

    protected:

	/// get the right part name from the TI webpage
	virtual void lookupPartName();
        /// fetch the data from the TI webpage
        virtual void lookup_IC();
	
    public:

};

#endif // IC_H
