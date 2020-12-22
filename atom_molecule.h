#ifndef ATOM_MOLECULE_H
#define ATOM_MOLECULE_H

#include "atom.h"

namespace lmpsdata {
class Atom_Molecule : public Atom
{
    public:
        //inherited virtual methods
        void* copy();
        void read(std::string&);
        void write(std::ostream&);
};
}
#endif // ATOM_MOLECULE_H
