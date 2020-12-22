#include "dihedral.h"
using namespace lmpsdata;
using namespace std;

void* Dihedral::copy()
{
    return new Dihedral(*this);
}
