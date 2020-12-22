#ifndef ABD_H
#define ABD_H

#include "lammps_type_interface.h"
#include <cstdint>
#include <valarray>

namespace lmpsdata {
class Abd: public lti
{
    public:
    //constructor and destructors
    Abd(unsigned ids) : atom_ids(ids) {}
    virtual ~Abd() {};

    //inherited virtual methods
    void* copy() =0;
    void read(std::string&);
    void write(std::ostream&);

    //setters and getters
    uint64_t& get_type();
    std::valarray<uint64_t>& get_atom_ids();
protected:
    //members
    uint64_t type;
    std::valarray<uint64_t> atom_ids;
private:
    //methods
    void read_type(std::string&);
    void write_type(std::ostream&);

    void read_atom_ids(std::string&);
    void write_atom_ids(std::ostream&);
};
}

#endif // ABD_H
