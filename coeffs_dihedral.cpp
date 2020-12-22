#include "coeffs_dihedral.h"
using namespace lmpsdata;
using namespace std;

void* Coeffs_dihedral::copy()
{
    return new Coeffs_dihedral(*this);
}

void Coeffs_dihedral::read_atom_types(string& line)
{
    string::size_type st = 0;
    atom_types.push_back(set<uint64_t>());
    for (int i = 0; i < 4; i++)
        atom_types.back().insert(stoull(line, &st));
}

