#ifndef IC_TI_H
#define IC_TI_H

#include "IC.h"
#include <string.h>
#include <curl/curl.h>


/**
 * @brief calculate the FIT of TI ICs
 * FIT value can be looked up from Webpage
 */
class IC_TI : public IC {
    public:
        /**
         * Constructor of the IC
         * @param name
         * @param elfr_value ELFR value itself
         * @param elfr_unit ELFR unit
         * @param fit FIT value itself
         * @param fit_temperature temperature of the given FIT
         * @param fit_unit  Unit of the given FIT
         */
        IC_TI(std::string name, std::string type);
        virtual ~IC_TI();

    protected:
        /// given FIT value
        float FIT;

        /// temperature the FIT value is valid
        float FIT_temperature;

    private:
        CURL *curl;

        void lookup_IC();
        std::string ICname;

    public:
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

};

#endif // IC_H
