#include "coeffs_bond.h"

#include "coeffs_bond.h"
using namespace lmpsdata;
using namespace std;

void* Coeffs_bond::copy()
{
    return new Coeffs_bond(*this);
}

void Coeffs_bond::read_atom_types(string& line)
{
    string::size_type st = 0;
    atom_types.push_back(set<uint64_t>());
    for (int i = 0; i < 2; i++)
        atom_types.back().insert(stoull(line, &st));
}
