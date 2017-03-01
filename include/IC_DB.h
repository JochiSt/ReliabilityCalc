#ifndef IC_DB_H
#define IC_DB_H

#include "IC_ELFR.h"
#include <string.h>
#include <vector>
#include <curl/curl.h>

#include "sqlite3_handler.h"

/**
 * @brief calculate the FIT of ICs and store data in database
 * FIT value is looked up from Webpage
 */
class IC_DB : public IC_ELFR {
    public:
        /**
         * Constructor of the IC
         * \param[in] name
         * \param[in] type correct naming of the IC (e.g. DS30EA101SQ/NOPB)
         */
        IC_DB(std::string name, std::string type);
        virtual ~IC_DB();

    protected:
        /// handler for the access to the webpage
        CURL *curl;

	/// get the right part name from the webpage
	virtual void lookupPartName() = 0;
        /// fetch the data from the webpage
        virtual void lookup_IC() = 0;

        /// store the naming of the IC
        std::string ICname;

	/// Handler for the SQLite3 database connection
	static sqlite3_handler db;
	/// function, which stores all values in database
	virtual void store_in_DB();
	/// lookup IC in database
	virtual bool lookup_IC_DB();
	
	/// Vector to store the values from TI webpage
    	std::vector<float> results;

	/// Create new table
	virtual void createTable();

    public:
        /**
         * \brief callback function for CURL
         */
        static int curl_writeCallback(char *inBuffer, size_t size, size_t count, std::string *outBuffer){
                outBuffer->append(inBuffer);
                return count*size;
        }

        /**
         * \brief replace all
         * \param[in,out] text text where to replace
         * \param[in] fnd text which should be replaced
         * \param[in] rep text to replace with
         */
        static void replace_all(std::string& text,const std::string& fnd,const std::string& rep){
                size_t pos = text.find(fnd);
                while(pos!=std::string::npos){
                        text.replace(pos,fnd.length(),rep);
                        pos = text.find(fnd,pos+rep.length());
                }
        }

	static void replace_tag(std::string& text, const std::string& fnd, const std::string& rep){
		std::string find = std::string("<") + fnd;
                size_t pos = text.find(find);
		size_t end = text.find(">", pos);
                while(pos!=std::string::npos && end!=std::string::npos){
                        text.replace(pos,end-pos+1,rep);
                        pos = text.find(find,pos+rep.length());
			end = text.find(">", pos);
                }
	}
};

#endif // IC_H
