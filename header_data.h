#ifndef HEADER_DATA_H
#define HEADER_DATA_H


#include <string>
#include <fstream>
#include <cstdint>
#include <vector>
#include <map>

namespace lmpsdata {
class header_data
{//LAMMPS header information
	//only the point particle header information has been implemented
	//since the current atom base class is designed for point particles only
public:
    header_data():xdim(2), ydim(2), zdim(2), tiltdim(3) {}
    virtual ~header_data() {}
	//methods
	void read(const std::string &, const std::string &);
	void write(std::ofstream &, const std::string &); //this write command will replace the one
	std::string check_header_keyword(const std::string &, bool &);
	uint64_t get(const std::string&);
	std::vector<double>& get_vector(const std::string&);
	void set(const std::string&, uint64_t);
	void set_vector(const std::string&, std::vector<double>&);

private:
    //methods
	void read_dimension(const std::string&, const std::string&);
	void write_dimension(std::ofstream&, const std::string&);

    //members
    uint64_t atomnum = 0;
    uint64_t bondnum = 0;
    uint64_t anglenum = 0;
    uint64_t dihedralnum = 0;
    uint64_t impropernum = 0;
    uint64_t atomtypenum = 0;
    uint64_t bondtypenum = 0;
    uint64_t angletypenum = 0;
    uint64_t dihedraltypenum = 0;
    uint64_t impropertypenum = 0;
    uint64_t extrabondnum = 0;

	std::vector<double> xdim;
	std::vector<double> ydim;
    std::vector<double> zdim;
    std::vector<double> tiltdim;//for use with triclinic system

    std::map<std::string, uint64_t&> int_map  {
        {"atoms", atomnum},
        {"bonds", bondnum},
        {"angles", anglenum},
        {"dihedrals", dihedralnum},
        {"impropers", impropernum},
        {"atom types", atomtypenum},
        {"bond types", bondtypenum},
        {"angle types", angletypenum},
        {"dihedral types", dihedraltypenum},
        {"improper types", impropertypenum},
        {"extra bond per atom", extrabondnum},
	};
	std::map<std::string, std::vector<double>&> v_map {
	    {"xlo xhi", xdim},
	    {"ylo yhi", ydim},
        {"zlo zhi", zdim},
        {"xy xz yz", tiltdim}
	};
};
}

#endif // HEADER_DATA_H
