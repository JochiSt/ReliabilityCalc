#ifndef IC_MAXIM_H
#define IC_MAXIM_H

#include "IC_DB.h"
#include <string.h>
#include <vector>
#include <curl/curl.h>

#include "sqlite3_handler.h"

/**
 * @brief calculate the FIT of MAXIM ICs
 * FIT value is looked up from Webpage
 */
class IC_MAXIM : public IC_DB {
    public:
        /**
         * Constructor of the IC
         * \param[in] name
         * \param[in] type correct naming of the IC (e.g. DS30EA101SQ/NOPB)
         */
        IC_MAXIM(std::string name, std::string type);
        virtual ~IC_MAXIM();

	struct ic_data_t {
	   int sample_size;
	   int rejects;
	   float FIT_25;
	   float FIT_55;
    	};

    protected:
	/// get the right part name from the TI webpage
	virtual void lookupPartName();
        /// fetch the data from the TI webpage
        virtual void lookup_IC();
	
	ic_data_t maxim_data;
	
    public:

};

#endif // IC_H
