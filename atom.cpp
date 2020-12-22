#include "atom.h"
#include <stdexcept>
using namespace lmpsdata;
using namespace std;

void* Atom::copy()
{
    return new Atom(*this);
}


void Atom::read(string& line)
{
    read_type(line);
    read_position(line);
    read_image(line);
}

void Atom::write(ostream& file)
{
    write_type(file);
    write_position(file);
    write_image(file);
    file << "\n";
}

void Atom::read_image(std::string& line)
{
    string::size_type st = 0;
    unsigned iterations = 0;
    while (!line.empty()) {
        if (iterations < image.size()) {
            image[iterations] = stoll(line, &st);
            line = line.substr(st);
            st = 0;//reset size_type to its original value
            iterations += 1;
        }
        else{
            throw ios_base::failure("there is too much information in this line does not match the format of the current atom style");
        }
    }
}

void Atom::write_image(std::ostream& file)
{
	for (unsigned i = 0; i < image.size(); i++) {
		file << image[i] << " " ;
	}
}

void Atom::read_position(std::string& line)
{
    string::size_type st = 0;
	for (int i = 0; i < 3; i++) {
        position[i] = stod(line, &st);
        line = line.substr(st);
        st = 0; //reset size_type to its original value
	}
}

void Atom::write_position(std::ostream& file)
{
	for (int i = 0; i < 3; i++) {
		file << position[i] << " " ;
	}
}

void Atom::read_charge(std::string& line)
{
    string::size_type st = 0;
    charge = stod(line, &st);
    line = line.substr(st);
}

void Atom::write_charge(std::ostream& file)
{
    file  << charge << " ";
}

void Atom::read_molecule(std::string& line)
{
    string::size_type st = 0;
    molecule = stoull(line, &st);
    line = line.substr(st);
}

void Atom::write_molecule(std::ostream& file)
{
    file << molecule << " ";
}

void Atom::read_type(std::string& line)
{
    string::size_type st = 0;
    type = stoull(line, &st);
    line = line.substr(st);
}

void Atom::write_type(std::ostream& file)
{
    file << type << " ";
}

uint64_t& Atom::get_type()
{
    return type;
}

valarray<double>& Atom::get_position()
{
    return position;
}

valarray<int64_t>& Atom::get_image()
{
    return image;
}

uint64_t& Atom::get_molecule()
{
    return molecule;
}

double& Atom::get_charge()
{
    return charge;
}
