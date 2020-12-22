#ifndef COEFFS_DIHEDRAL_H
#define COEFFS_DIHEDRAL_H

#include "coeffs.h"

namespace lmpsdata {
class Coeffs_dihedral : public Coeffs
{
    public:
        //inherited virtual methods
        void* copy();
        void read_atom_types(std::string& line);
};
}

#endif // COEFFS_DIHEDRAL_H
