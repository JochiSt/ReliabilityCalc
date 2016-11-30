#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "component.h"

class inductor : public component
{
    public:
        /**
         * Constructor of Inductor
         * \param name      internal naming of inductor, e.g. L1, L2
         */
        inductor(std::string name);
        virtual ~inductor();

        virtual float getFIT() = 0;

        static std::string getIdentifier(){
            return identifier;
        }
        static unsigned int getPartCount(){
            return partcnt;
        }

    protected:

    private:
        static std::string identifier;
        static unsigned int partcnt;
};

#endif // INDUCTOR_H
