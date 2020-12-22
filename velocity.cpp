#include "velocity.h"
using namespace lmpsdata;
using namespace std;

void* Velocity::copy()
{
    return new Velocity(*this);
}

void Velocity::read(string& line)
{
    read_value(line);
}

void Velocity::write(ostream& file)
{
    write_value(file);
    file << "\n";
}

void Velocity::read_value(string& line)
{
    string::size_type st = 0;
    for (int i = 0; i < 3; i++)
        value[i] = stod(line, &st);
}

void Velocity::write_value(ostream& file)
{
    for (int i = 0; i < 3; i++)
        file << value[i] << " ";
}

valarray<double>& Velocity::get_value()
{
    return value;
}
