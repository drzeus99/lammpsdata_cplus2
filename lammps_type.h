#ifdef LAMMPS_TYPE_CONSTRUCTOR
    type_style(atom, Atom, atom)
    type_style(full, Full, atom)
    type_style(molecule, Atom_Molecule, atom)
    type_style(Bonds, Bond, abd)
    type_style(Angles, Angle, abd)
    type_style(Dihedrals, Dihedral, abd)
    type_style(Impropers, Dihedral, abd)
    type_style(Masses, Mass, mass)
    type_style(Angle Coeffs, Coeffs_angle, coeffs)
    type_style(Bond Coeffs, Coeffs_bond, coeffs)
    type_style(Dihedral Coeffs, Coeffs_dihedral, coeffs)
    type_style(Improper Coeffs, Coeffs_dihedral, coeffs)
   // type_style(Pair Coeffs, Pair_coeffs, pair_coeffs)
  //  type_style(PairIJ Coeffs, Pair_coeffs, pair_coeffs)
    type_style(Velocities, Velocity, velocity)
#elif defined LAMMPS_TYPE_INTERFACE
   lti(atom, atom)
   lti(full, atom)
   lti(molecule, atom)
   lti(Bonds, abd)
   lti(Angles, abd)
   lti(Dihedrals, abd)
   lti(Impropers, abd)
   lti(Masses, mass)
   lti(Angle Coeffs, coeffs)
   lti(Bond Coeffs, coeffs)
   lti(Dihedral Coeffs, coeffs)
   lti(Improper Coeffs, coeffs)
   //lti(Pair Coeffs, pair_coeffs)
   //lti(PairIJ Coeffs, pair_coeffs)
   lti(Velocities, velocity)
#elif defined U_PROPERTY
    prop(atom, atom, molecule)
    prop(atom, atom, type)
    prop(full, atom, molecule)
    prop(full, atom, type)
    prop(molecule, atom, molecule)
    prop(molecule, atom, type)
    prop(Bonds, abd, type)
    prop(Angles, abd, type)
    prop(Dihedrals, abd, type)
    prop(Impropers, abd, type)
#elif defined D_PROPERTY
    prop(atom, atom, charge)
    prop(full, atom, charge)
    prop(molecule, atom, charge)
    prop(Masses, mass, value)
#elif defined S_PROPERTY
    prop(Angle Coeffs, coeffs, info)
    prop(Bond Coeffs, coeffs, info)
    prop(Dihedral Coeffs, coeffs, info)
    prop(Improper Coeffs, coeffs, info)
    //prop(Pair Coeffs, pair_coeffs, info)
   // prop(PairIJ Coeffs, pair_coeffs, info)
#elif defined U_V_PROPERTY
    prop(Bonds, abd, atom_ids)
    prop(Angles, abd, atom_ids)
    prop(Dihedrals, abd, atom_ids)
    prop(Impropers, abd, atom_ids)
#elif defined I_V_PROPERTY
    prop(atom, atom, image)
    prop(full, atom, image)
    prop(molecule, atom, image)
#elif defined D_V_PROPERTY
    prop(atom, atom, position)
    prop(full, atom, position)
    prop(molecule, atom, position)
    prop(Velocities, velocity, value)
#else
    #ifndef LAMMPS_TYPE
    #define LAMMPS_TYPE

    #include <map>
    #include <memory>
    #include <string>
    #include <fstream>
    #include "atom.h"
    #include "atom_molecule.h"
    #include "full.h"
    #include "bond.h"
    #include "angle.h"
    #include "dihedral.h"
    #include "mass.h"
    #include "coeffs_angle.h"
    #include "coeffs_bond.h"
    #include "coeffs_dihedral.h"
    #include "pair_coeffs.h"
    #include "velocity.h"
    namespace lmpsdata {
    struct lammps_type
    {
        union value {
            Atom* atom;
            Abd* abd;
            Mass* mass;
            Coeffs* coeffs;
            //Pair_coeffs* pair_coeffs;
            Velocity* velocity;
        } v;
        std::string key;
        //property access
        uint64_t& u_property(const std::string&);
        //int64_t& i_property(const std::string&); //!not used yet
        double& d_property(const std::string&);
        std::string& s_property(const std::string&);
        std::valarray<uint64_t>& u_v_property(const std::string&);
        std::valarray<int64_t>& i_v_property(const std::string&);
        std::valarray<double>& d_v_property(const std::string&);
        //std::valarray<std::string>& s_v_property(const std::string&); //!not used yet
        //read/write
        void read(std::string& line);
        void write(std::ostream& os);
        //constructor
        lammps_type(const std::string& key);
        //copy constructor connected to lti
        lammps_type(std::shared_ptr<lammps_type>& obj);
        //destructor
        ~lammps_type();
        //deleted copy constructor and assignment operator
        lammps_type(const lammps_type&) = delete;
        lammps_type& operator= (const lammps_type&) = delete;
        //static objects
    private:
        //object creation
        typedef void (*type_creator) (lammps_type*);
        static std::map<std::string, type_creator>* constructor_map;
        static std::map<std::string, type_creator>* initialize_constructors();
        //object copying
        typedef void (*type_copier) (lammps_type*, lammps_type*);
        static std::map<std::string, type_copier>* copier_map;
        static std::map<std::string, type_copier>* initialize_copiers();
        //object deleting
        typedef void (*type_dest) (lammps_type*);
        static std::map<std::string, type_dest>* dest_map;
        static std::map<std::string, type_dest>* init_dest();
        //object reading
        typedef void (*type_reader) (lammps_type*, std::string&);
        static std::map<std::string, type_reader>* reader_map;
        static std::map<std::string, type_reader>* initialize_readers();
        //object writing
        typedef void (*type_writer) (lammps_type*, std::ostream&);
        static std::map<std::string, type_writer>* writer_map;
        static std::map<std::string, type_writer>* initialize_writers();
        //property access
        //uint64_t properties
        typedef uint64_t& (*u_prop) (lammps_type*);
        static std::map<std::pair<std::string, std::string>, u_prop> u_props;
        static std::map<std::pair<std::string, std::string>, u_prop> init_u_props();
        //int64_t properties
        //!not used yet
        //double properties
        typedef double& (*d_prop) (lammps_type*);
        static std::map<std::pair<std::string, std::string>, d_prop> d_props;
        static std::map<std::pair<std::string, std::string>, d_prop> init_d_props();
        //string properties
        typedef std::string& (*s_prop) (lammps_type*);
        static std::map<std::pair<std::string, std::string>, s_prop> s_props;
        static std::map<std::pair<std::string, std::string>, s_prop> init_s_props();
        //valarray uint64_t properties
        typedef std::valarray<uint64_t>& (*u_v_prop) (lammps_type*);
        static std::map<std::pair<std::string, std::string>, u_v_prop> u_v_props;
        static std::map<std::pair<std::string, std::string>, u_v_prop> init_u_v_props();
        //valarray int64_t properties
        typedef std::valarray<int64_t>& (*i_v_prop) (lammps_type*);
        static std::map<std::pair<std::string, std::string>, i_v_prop> i_v_props;
        static std::map<std::pair<std::string, std::string>, i_v_prop> init_i_v_props();
        //valarray double properties
        typedef std::valarray<double>& (*d_v_prop) (lammps_type*);
        static std::map<std::pair<std::string, std::string>, d_v_prop> d_v_props;
        static std::map<std::pair<std::string, std::string>, d_v_prop> init_d_v_props();
        //valarray string properties
        //!not used yet
    };
    //shared_ptr typedef
    typedef std::shared_ptr<lammps_type> lammps_type_ptr;
    //lammps_type macros for working with union type when the fld is not a string
    #define atom_field(lt, fld) (lt->v.atom->get_##fld())
    #define abd_field(lt, fld) (lt->v.abd->get_##fld())
    #define mass_field(lt, fld) (lt->v.mass->get_##fld())
    #define coeffs_field(lt, fld) (lt->v.coeffs->get_##fld())
    //#define pair_coeffs_field(lt, fld) (lt->v.pair_coeffs->get_##fld())
    #define velocity_field(lt, fld) (lt->v.velocity->get_##fld())
    }
#endif // LAMMPS_TYPE
#endif // LAMMPS_TYPE_CONSTRUCTOR

