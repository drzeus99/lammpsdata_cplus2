#include "pair_coeffs.h"
using namespace lmpsdata;
using namespace std;

void* Pair_coeffs::copy()
{
    return new Pair_coeffs(*this);
}

void Pair_coeffs::read(string& line)
{
    read_info(line);
}

void Pair_coeffs::write(ostream& file)
{
    write_info(file);
    file << "\n";
}

void Pair_coeffs::read_info(std::string& line)
{
    info = line;
}

void Pair_coeffs::write_info(std::ostream& file)
{
    file << info << " ";
}

string& Pair_coeffs::get_info()
{
    return info;
}
