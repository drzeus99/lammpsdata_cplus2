#ifndef ANGLE_H
#define ANGLE_H

#include "abd.h"

namespace lmpsdata {
class Angle : public Abd
{
    public:
        //constructors and destructors
        Angle() : Abd(3) {}
        //inherited virtual methods
        void* copy();
};
}
#endif // ANGLE_H
