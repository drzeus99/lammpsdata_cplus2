#include "header_data.h"
#include <stdexcept>
using namespace lmpsdata;

void header_data::read(const std::string& data, const std::string& keyword)
{
    try {
        int_map.at(keyword) = stoull(data);
    } catch (std::exception& e) {
        try {
            read_dimension(data, keyword);
        } catch (std::exception& e) {
            throw std::invalid_argument("the keyword " + keyword + " is not a valid input for the header_data class currently");
        }
    }
}

std::string header_data::check_header_keyword(const std::string &input, bool &test)//note you have to copy the object string you can
//not pass by reference since the string output wont exist after the method is finished.
{
	//initialize output string to an empty string
	std::string output="";
	//initialize test to false
	test = false;

	std::string header_keyword[15] = {"atoms", "bonds", "angles", "dihedrals", "impropers",
		"atom types", "bond types", "angle types", "dihedral types", "improper types",
		"extra bond per atom", "xlo xhi", "ylo yhi", "zlo zhi", "xy xz yz"};
	for (int i = 0; i < 15; i++) {
		if (input.find(header_keyword[i]) != std::string::npos){
            test = true;
            output = header_keyword[i];
            break;
        }
	}
	return output;
}

void header_data::write(std::ofstream &file, const std::string &keyword)
{
    try {
        file << int_map.at(keyword) << " ";
    } catch (std::exception& e) {
        try {
            write_dimension(file, keyword);
        } catch (std::exception& e) {
            throw std::invalid_argument("the keyword " + keyword + " is not a valid input for the header_data::write");
        }
    }
	file << keyword << std::endl;
}

void header_data::read_dimension(const std::string& info, const std::string& keyword)
{
    std::vector<double>& data = v_map.at(keyword);
    std::string::size_type ss=0;
    std::string line = info;
	for (auto& value: data) {
        value = stod(line, &ss);
        line = line.substr(ss);
	}
}

void header_data::write_dimension(std::ofstream &file, const std::string& keyword)
{
    std::vector<double>& data = v_map.at(keyword);
	for (auto value: data) {
		file << value <<  " ";
	}
}

uint64_t header_data::get(const std::string& keyword)
{
    return int_map.at(keyword);
}

void header_data::set(const std::string& keyword, uint64_t value)
{
    int_map.at(keyword) = value;
}

std::vector<double>& header_data::get_vector(const std::string& keyword)
{
    return v_map.at(keyword);
}

void header_data::set_vector(const std::string& keyword, std::vector<double>& value)
{
    v_map.at(keyword) = value;
}
