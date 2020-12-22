#ifndef PAIR_COEFFS_H
#define PAIR_COEFFS_H

#include "lammps_type_interface.h"

namespace lmpsdata {
class Pair_coeffs: public lti
{
    public:
        //inherited virtual methods
        void* copy();
        void read(std::string&);
        void write(std::ostream&);

        //getters and setters
        std::string& get_info();

    private:
        //member
        std::string info;

        //methods
        void read_info(std::string&);
        void write_info(std::ostream&);
};
}

#endif // PAIR_COEFFS_H
