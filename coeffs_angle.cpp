#include "coeffs_angle.h"
using namespace lmpsdata;
using namespace std;

void* Coeffs_angle::copy()
{
    return new Coeffs_angle(*this);
}

void Coeffs_angle::read_atom_types(string& line)
{
    string::size_type st = 0;
    atom_types.push_back(set<uint64_t>());
    for (int i = 0; i < 3; i++)
        atom_types.back().insert(stoull(line, &st));
}
