#ifndef DIHEDRAL_H
#define DIHEDRAL_H

#include "abd.h"

namespace lmpsdata {
class Dihedral : public Abd
{
    public:
        //constructor and destructors
        Dihedral() : Abd(4) {}

        //inherited virtual methods
        void* copy();
};
}

#endif // DIHEDRAL_H
