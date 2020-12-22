#ifndef COEFFS_BOND_H
#define COEFFS_BOND_H

#include "coeffs.h"

namespace lmpsdata {
class Coeffs_bond: public Coeffs
{
    public:
        //inherited virtual methods
        void* copy();
        void read_atom_types(std::string& line);
};
}

#endif // COEFFS_BOND_H
