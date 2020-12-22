#ifndef MASS_H
#define MASS_H

#include "lammps_type_interface.h"

namespace lmpsdata {
class Mass : public lti
{
    public:
        //inherited virtual method
        void* copy();
        void read(std::string&);
        void write(std::ostream&);

        //setters and getters
        double& get_value();
    private:
        //member
        double value;

        //methods
        void read_value(std::string &);
        void write_value(std::ostream &);
};
}

#endif // MASS_H
