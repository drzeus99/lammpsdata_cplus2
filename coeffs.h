#ifndef COEFFS_H
#define COEFFS_H

#include "lammps_type_interface.h"
#include <vector>
#include <set>
#include <cstdint>
namespace lmpsdata {
class Coeffs : public lti
{
    public:
        //constructors and destructors
        virtual ~Coeffs() {}

        //inherited virtual methods
        void* copy() = 0;
        void read(std::string&);
        void write(std::ostream&);

        //getters and setters
        std::string& get_info();

        //methods for reading in atom types and testing if the atom types match the coeffs object.
        virtual void read_atom_types(std::string&) = 0;
        bool atom_type_match(std::vector<uint64_t>&);
    protected:
        //member
        std::vector<std::set<uint64_t>> atom_types; //atom types that use these coeffs
    private:
        //member
        std::string info;//list of coeffs
        bool test_result;

        //methods
        void read_info(std::string&);
        void write_info(std::ostream&);
};
}

#endif // COEFFS_H
