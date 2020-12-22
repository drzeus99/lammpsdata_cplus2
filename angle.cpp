#include "angle.h"
using namespace lmpsdata;
using namespace std;

void* Angle::copy()
{
    return new Angle(*this);
}
