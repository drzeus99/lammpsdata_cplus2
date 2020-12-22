#include "full.h"
using namespace lmpsdata;
using namespace std;

void* Full::copy()
{
    return new Full(*this);
}

void Full::read(string& line)
{
    read_molecule(line);
    read_type(line);
    read_charge(line);
    read_position(line);
    read_image(line);
}

void Full::write(ostream& file)
{
    write_molecule(file);
    write_type(file);
    write_charge(file);
    write_position(file);
    write_image(file);
    file << "\n";
}
