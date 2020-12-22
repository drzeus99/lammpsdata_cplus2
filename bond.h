#ifndef BOND_H
#define BOND_H

#include "abd.h"

namespace lmpsdata {
class Bond : public Abd
{
    public:
        //constructors and destructors
        Bond() : Abd(2) {}

        //inherited virtual methods
        void* copy();
};
}

#endif // BOND_H
