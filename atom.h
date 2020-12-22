#ifndef ATOM_H
#define ATOM_H


#include <valarray>
#include <cstdint>
#include "lammps_type_interface.h"

//note:the methods that are part of the standard_interface do not need to be made virtual in this class
//these are add, replace, read, and write
namespace lmpsdata{
class Atom: public lti
//base type atom class -> corresponds to atom style atomic and colloid
{
    public:
        //constructors & destructors
        Atom() : position(3), image(3) {}
        virtual ~Atom() {}

        //inherited virtual methods
        void* copy();
        void read(std::string&);
        void write(std::ostream&);

        //getters and setters
        uint64_t& get_type();
        std::valarray<double>& get_position();
        std::valarray<int64_t>& get_image();
        uint64_t& get_molecule();
        double& get_charge();
    protected:
        //members
        uint64_t type;//atomtype
        std::valarray<double> position;
        std::valarray<int64_t> image;
        uint64_t molecule; //only used by molecule class and full class
        double charge; //only used by full class

        //methods
        void read_image(std::string&);
        void write_image(std::ostream&);

        void read_position(std::string&);
        void write_position(std::ostream&);

        void read_type(std::string&);
        void write_type(std::ostream&);

        void read_molecule(std::string&);
        void write_molecule(std::ostream&);

        void read_charge(std::string&);
        void write_charge(std::ostream&);
};
}
#endif // ATOM_H
