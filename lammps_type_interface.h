#ifndef L_T_I
#define L_T_I
#include <string>
#include <fstream>
namespace lmpsdata {
struct lti //lammps_type_interface
{
    virtual void* copy()=0;
    virtual void read(std::string&) =0;
    virtual void write(std::ostream&) =0;
    virtual ~lti() {}
};
}
#endif // L_T_I
