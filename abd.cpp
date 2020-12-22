#include "abd.h"
using namespace lmpsdata;
using namespace std;

void Abd::read(string& line)
{
	read_type(line);
	read_atom_ids(line);
}

void Abd::write(ostream& file)
{
	write_type(file);
	write_atom_ids(file);
	file << "\n";
}

void Abd::read_type(std::string& line)
{
	string::size_type st = 0;
	type = stoull(line, &st);
	line = line.substr(st);
}

void Abd::write_type(std::ostream& file)
{
	file << type << " ";
}

void Abd::read_atom_ids(std::string& line)
{
	string::size_type st = 0;
	for (unsigned i = 0; i < atom_ids.size(); i++) {
		atom_ids[i] = stoull(line, &st);
		line = line.substr(st);
		st = 0; //reset size_type to 0
	}
}

void Abd::write_atom_ids(std::ostream& file)
{
	for (auto val: atom_ids)
		file << val << " ";
}

uint64_t& Abd::get_type()
{
	return type;
}

valarray<uint64_t>& Abd::get_atom_ids()
{
	return atom_ids;
}
