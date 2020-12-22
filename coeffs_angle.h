#ifndef COEFFS_ANGLE_H
#define COEFFS_ANGLE_H

#include "coeffs.h"

namespace lmpsdata {
class Coeffs_angle : public Coeffs
{
    public:
        //inherited virtual methods
        void* copy();
        void read_atom_types(std::string& line);
};
}

#endif // COEFFS_ANGLE_H
