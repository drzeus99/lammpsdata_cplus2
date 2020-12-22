#include "atom_molecule.h"
using namespace lmpsdata;
using namespace std;

void* Atom_Molecule::copy()
{
    return new Atom_Molecule(*this);
}


void Atom_Molecule::read(string& line)
{
    read_molecule(line);
    read_type(line);
    read_position(line);
    read_image(line);
}

void Atom_Molecule::write(ostream& file)
{
    write_molecule(file);
    write_type(file);
    write_position(file);
    write_image(file);
    file << "\n";
}
