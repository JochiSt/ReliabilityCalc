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

	/**
	 * struct to put all data from website into map
	 */
	struct ic_data_t {
	   int sample_size;	///< global number of samples
	   int rejects;		///< number of rejected ICs
	   float FIT_25;	///< FIT value at 25°C
	   float FIT_55;	///< FIT value at 55°C
    	};

    protected:
	/// get the right part name from the TI webpage
	virtual void lookupPartName();
        /// fetch the data from the TI webpage
        virtual void lookup_IC();
	
	/// local variable for storage of data
	ic_data_t maxim_data;
	
};

#endif // IC_H
