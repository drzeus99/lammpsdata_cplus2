#include "bond.h"
using namespace lmpsdata;
using namespace std;

void* Bond::copy()
{
    return new Bond(*this);
}
