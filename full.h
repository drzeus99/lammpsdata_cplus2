#ifndef FULL_H
#define FULL_H

#include "atom.h"

namespace lmpsdata {
class Full : public Atom
{
    public:
        //inherited virtual methods
        void* copy();
        void read(std::string&);
        void write(std::ostream&);
};
}

#endif // FULL_H
