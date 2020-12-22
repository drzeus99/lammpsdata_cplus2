#include "mass.h"
using namespace lmpsdata;
using namespace std;

void* Mass::copy()
{
    return new Mass(*this);
}

void Mass::read(string& line)
{
    read_value(line);
}

void Mass::write(ostream& file)
{
    write_value(file);
    file << "\n";
}

void Mass::read_value(std::string &line)
{
	value = stod(line);
}

void Mass::write_value(std::ostream& file)
{
	file << value << " ";
}

double& Mass::get_value()
{
    return value;
}
