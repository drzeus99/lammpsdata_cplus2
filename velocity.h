#ifndef VELOCITY_H
#define VELOCITY_H

#include "lammps_type_interface.h"
#include <valarray>

namespace lmpsdata {
class Velocity : public lti
{
    public:
        //constructors
        Velocity(): value(3) {}

        //inherited virtual methods
        void* copy();
        void read(std::string&);
        void write(std::ostream&);

        //getters and setters
        std::valarray<double>& get_value();

    private:
        //member
        std::valarray<double> value;

        //methods
        void read_value(std::string &);
        void write_value(std::ostream &);
};
}

#endif // VELOCITY_H
