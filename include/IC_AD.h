#ifndef IC_AD_H
#define IC_AD_H

#include "IC_DB.h"
#include <string.h>
#include <vector>
#include <curl/curl.h>

#include "sqlite3_handler.h"

/**
 * @brief calculate the FIT of Analog Devices ICs
 * FIT value is looked up from Webpage
 */
class IC_AD : public IC_DB {
    public:
        /**
         * Constructor of the IC
         * \param[in] name (e.g. U100)
         * \param[in] type correct naming of the IC (e.g. DS30EA101SQ/NOPB)
         */
        IC_AD(std::string name, std::string type);
        virtual ~IC_AD();


    protected:
	/// get the right part name from the TI webpage
	virtual void lookupPartName();
        /// fetch the data from the TI webpage
        virtual void lookup_IC();
};

#endif // IC_H
