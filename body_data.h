#ifndef BODY_DATA_H
#define BODY_DATA_H
//!need to redo core functionality and than rebuild rest later

#include "kmap.h"
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <cstdint>
#include <thread>
#include "lammps_type.h"

namespace lmpsdata{
//Ellipsoids, Lines, Triangles, and Bodies are not implented
//class 2 force field purposely not implemented
class body_data
{
public:
    //copy constructor which does deep copy
//!	body_data(body_data&);

	//assignment operator which does shallow copying
//!	body_data& operator=(body_data&);

	//destructor
	virtual ~body_data();

	//method to check if a string contains a body_data keyword than returns the body_data keyword
	//otherwise returns an empty string
	std::string check_body_keyword(const std::string&);

	//finds the kmap or kvector which matches the keyword then deletes the pointers and clears the kmap/kvector
	void delete_body_data(const std::string &);

	//deletes the pointer stored in the kmap M at key value K
	//than erases the key value
	//this process ensures no memory will be leaked
//!	void erase_key(const std::string&, const uint64_t);

    //moves the pointer stored in the kmap M at key value K
    //to a different body data object
    //than erases the key value but does not decrease pointer ref count
//!    void move_key(const std::string&, kmap<uint64_t, void*>&, const uint64_t);

    //moves the pointer stored in the kvector pair_coeff
    //at the specified index to a new body_data object
    //uses cool logic and wizardry to turn this operation into an O(1) operation
    //!void move_index(const std::string&, kvector<void*>&, const uint64_t);

    //increase the ref count of the value stored at key from the inputed kmap
    //!void copy_key(const std::string&, kmap<uint64_t, void*>&, const uint64_t);

    //increases the ref count of the value storead at index from the inputed kvector
    //!void copy_index(const std::string&, kvector<void*>&, const uint64_t);

	//produces a new copy of the value stored at key from the inputed kmap
    //!void* deep_copy_key(const std::string&, kmap<uint64_t, void*>&, const uint64_t);

    //produces a new copy of the value stored at index from the inputed kvector
    //!void* deep_copy_index(const std::string&, kvector<void*>&, const uint64_t);

    //!there are no simple methods to deal with individual map and vector inserts
    //!that update the reference counter. These will have to be done individually
    //!using the methods in Void_manager

	//inserts the key and value into the appropriate kmap
	void mapinsert(const std::string&, uint64_t, lammps_type_ptr);

	//tests whether the kmap or kvector associated with the string is empty
	//!bool empty(const std::string &);

    //move an entire body_data class
    //!void move_body_data(body_data*);

    //move individual kmaps
    //!void move(const std::string&, body_data*);

	//copying an entire body_data class //increases ref count of pointers
	//!void copy_body_data(body_data*);

    //copy individual kmaps //increases ref count of pointers
	//!void copy(const std::string&, body_data*);

    //copying an entire body_data class //creates new pointers which are copies of another body_data class
	//!void deep_copy_body_data(body_data*);

    //copy indivdiaul kmaps //creates new pointers which are copies of another body_data class.
    //!void deep_copy(const std::string&, body_data*);

    //accessing kmaps from std::map container
	kmap<uint64_t, lammps_type_ptr>& get_map(const std::string&);

	const std::string& get_atom_style();

	void set_atom_style(const std::string&);

    //!static bool vector_property(const std::string&);

/*    //find the set of keys that have matching values in the data set corresponding to keyword
    std::unordered_set<uint64_t> find_set(std::string&, std::string&, uint64_t, int);

    std::unordered_set<uint64_t> find_set(std::string&, std::string&, int64_t, int);

    std::unordered_set<uint64_t> find_set(std::string&, std::string&, double, int);

    std::unordered_set<uint64_t> find_set(std::string&, std::string&, std::string, int);

    std::unordered_set<uint64_t> find_set(std::string&, std::string&, std::vector<uint64_t>&, int);

    std::unordered_set<uint64_t> find_set(std::string&, std::string&, std::vector<int64_t>&, int);

    std::unordered_set<uint64_t> find_set(std::string&, std::string&, std::vector<double>&, int);

    //return the dictionary that has matching values in the data set corresponding to keyword
    kmap<uint64_t, void*> find_map(std::string&, std::string&, uint64_t, int);

    kmap<uint64_t, void*> find_map(std::string&, std::string&, int64_t, int);

    kmap<uint64_t, void*> find_map(std::string&, std::string&, double, int);

    kmap<uint64_t, void*> find_map(std::string&, std::string&, std::string, int);

    kmap<uint64_t, void*> find_map(std::string&, std::string&, std::vector<uint64_t>&, int);

    kmap<uint64_t, void*> find_map(std::string&, std::string&, std::vector<int64_t>&, int);

    kmap<uint64_t, void*> find_map(std::string&, std::string&, std::vector<double>&, int);

    //returns a set of keys that match to one of a vector of values in the data set corresponding to keyword
    std::unordered_set<uint64_t> search_set(std::string&, std::string&, std::unordered_set<uint64_t>&, int);

    std::unordered_set<uint64_t> search_set(std::string&, std::string&, std::vector<uint64_t>&, int);

    std::unordered_set<uint64_t> search_set(std::string&, std::string&, std::vector<int64_t>&, int);

    std::unordered_set<uint64_t> search_set(std::string&, std::string&, std::vector<double>&, int);

    //return a map of keys that match to one of a vector of values in the data set corresponding to keyword
    kmap<uint64_t, void*> search_map(std::string&, std::string&, std::unordered_set<uint64_t>&, int);

    kmap<uint64_t, void*> search_map(std::string&, std::string&, std::vector<uint64_t>&, int);

    kmap<uint64_t, void*> search_map(std::string&, std::string&, std::vector<int64_t>&, int);

    kmap<uint64_t, void*> search_map(std::string&, std::string&, std::vector<double>&, int);*/

protected:
    //extracting a group of atoms with certain property values and their associated data structures
    //!virtual void extract(body_data*, const std::string&, const uint64_t, const int);

    //!virtual void extract(body_data*, const std::string&, const double, const int);

    //joining multiple body_data classes into the current body_data class
    //clears the current body_data class of all information before doing the join
    //than adds each body data class into current body_data class
    //!virtual void join(std::vector<body_data*>); //!may end up moving to either protected or private
    //link to function object

    //adds a body_data class to the current body_data class
    //keys are not conserved
    //increases ref count of pointers
    //different from copy_body_data in that keys are not conserved.
    //!virtual void add_body_data(body_data*); //!may end up moving to either protected or private
    //link to function object

    //method to convert vector of vector string into a kmap
	//and than add the map to the class
	//the vector of vector string is assumed to contain the key
	//the keys are not conserved.
	//!after addition of the map to the class the temporary map is deleted
	//!and cleared
	//!virtual void add(std::vector<std::vector<std::string> > &, const std::string &); //!may end up moving to either protected or private
	//link to function object

	//methods to append inputed kmaps and kvectors into the classes maps
	//these methods are different from copy in that the keys are not preserved
	//but the pointers will still be copied
	//!virtual void add(kmap<uint64_t, void*>&, const std::string&); //!may end up moving to protected or private
	//link to function object
    //!virtual void add(kvector<void*>&, const std::string&); //!may end up moving to protected or private
    //link to function object

private:
    std::map<std::string, kmap<uint64_t, lammps_type_ptr> > database {
            {"Atoms", kmap<uint64_t, lammps_type_ptr>()},
            {"Velocities", kmap<uint64_t, lammps_type_ptr>()},
            {"Masses", kmap<uint64_t, lammps_type_ptr>()},
            {"Angle Coeffs", kmap<uint64_t, lammps_type_ptr>()},
            {"Bond Coeffs", kmap<uint64_t, lammps_type_ptr>()},
            {"Dihedral Coeffs", kmap<uint64_t, lammps_type_ptr>()},
            {"Improper Coeffs", kmap<uint64_t, lammps_type_ptr>()},
            {"Angles", kmap<uint64_t, lammps_type_ptr>()},
            {"Bonds", kmap<uint64_t, lammps_type_ptr>()},
            {"Dihedrals", kmap<uint64_t, lammps_type_ptr>()},
            {"Impropers", kmap<uint64_t, lammps_type_ptr>()}
    };
    //!not sure what this is for
   /*! static std::set<std::string> vector_properties;
    static struct vector_property_init
    {
        vector_property_init()
        {
            vector_properties.insert("position");
            vector_properties.insert("image");
            vector_properties.insert("atom_ids");
            vector_properties.insert("value");
        }
    } _initializer;*/
    std::string atom_style;
/*
    template <class V>
    void find_set(std::string&, std::string&, V, int, std::unordered_set<uint64_t>&);

    template <class V>
    void find_map(std::string&, std::string&, V, int, kmap<uint64_t, void*>&);

    template <class V>
    void search_set(std::string&, std::string&, std::unordered_set<V>&, int, std::unordered_set<uint64_t>&);

    template <class V>
    void search_map(std::string&, std::string&, std::unordered_set<V>&, int, kmap<uint64_t, void*>&);*/
};
}
#endif // BODY_DATA_H
