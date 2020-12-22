#include "body_data.h"
#include <stdexcept>
#include <thread>
#include <array>
/*#include "extract_atoms.h"
#include "extract_coeficients.h"
#include "extract_velocities.h"
#include "extract_connections.h"*/
using namespace lmpsdata;
using namespace std;
//!need to redo core functionality and than rebuild rest later
//static initializers
/*!std::set<std::string> body_data::vector_properties;
body_data::vector_property_init body_data::_initializer;*/

//copy constructor which does deep copy
/*!body_data::body_data(body_data& other)
{
    deep_copy_body_data(&other);
}

//assignment operator which does shallow copying
body_data& body_data::operator=(body_data& other)
{
    copy_body_data(&other);
    return *this;
}*/

//destructor
body_data::~body_data()
{
    //create an array of all possible keywords
    array<string, 11> body_keywords = {"Atoms", "Masses", "Bond Coeffs", "Angle Coeffs",
                              "Dihedral Coeffs", "Improper Coeffs", "Velocities",
                              "Bonds", "Angles", "Dihedrals", "Impropers"
                              };
    //go through the array clearing the memory stored in the maps
    for (string& keyword: body_keywords)
    {
        delete_body_data(keyword);
    }
}

string body_data::check_body_keyword(const string &input) //note you have to copy the object string you can
//not pass by reference since the string output wont exist after the method is finished.
{
    //create an array of all possible keywords
    //note: This array differs from the destructor above because Pair Coeffs and PairIJ Coeffs
    //are separate because this method checks for valid keywords not keywords corresponding to
    //maps stored in body_data
    array<string, 11> body_keywords = {"Atoms", "Masses", "Bond Coeffs", "Angle Coeffs", "Dihedral Coeffs",
                               "Improper Coeffs", "Velocities",
                               "Bonds", "Angles", "Dihedrals", "Impropers"
                             };
    for (string& keyword: body_keywords)
    {
        if (input.find(keyword) != string::npos)
        {
            return keyword;
        }
    }
    return "";
}

void body_data::delete_body_data(const std::string& keyword)
{
    cout << "deleting body data keyword " << keyword << endl;
    try {
        kmap<uint64_t, lammps_type_ptr>& storage = get_map(keyword);
        storage.clear();
    }catch (std::exception& e) {
        throw std::invalid_argument("the keyword " + keyword + " is either not a valid LAMMPS body keyword or has not been implemented yet");
    }
}
/*
void body_data::erase_key(const std::string& keyword, const uint64_t key)
{
    try {
        kmap<uint64_t, void*>& storage = database.at(keyword);
        void_manager->get(keyword)->clear(storage[key]);
        storage.remove(key);
    }catch (std::exception& e) {
        throw std::invalid_argument("the keyword " + keyword + " is either not a valid LAMMPS body keyword or has not been implemented yet");
    }
}

//!note: you can't use this during the extraction process
//!the extraction process has its own move method
void body_data::move_key(const std::string& keyword, kmap<uint64_t, void*>& to_storage, const uint64_t key)
{
    try {
        kmap<uint64_t, void*>& from_storage = get_map(keyword);
        to_storage.insert(key, from_storage[key]);
        from_storage.remove(key);
    }
    catch (std::exception& e) {
        throw std::invalid_argument("the keyword " + keyword + " is either not a valid LAMMPS body keyword or has not been implemented yet");
    }
}

void body_data::move_index(const std::string& keyword, kvector<void*>& to_pair, const uint64_t index)
{
    try {
        kvector<void*>& from_pair = get_vector(keyword);
        to_pair.push_back(from_pair[index]);
        void* temp = from_pair[index];
        from_pair[index] = from_pair.back();
        from_pair.pop_back();
    }
    catch (std::exception& e) {
        throw std::invalid_argument("the keyword " + keyword + " is either not a valid LAMMPS body keyword or has not been implemented yet");
    }
}*/

/*
void body_data::copy_key(const std::string&, kmap<uint64_t, void*>&, const uint64_t);
{

}

void body_data::copy_index(const std::string&, kvector<void*>&, const uint64_t);
{

}*/

/*void* body_data::deep_copy_key(const std::string& keyword, kmap<uint64_t, void*>& storage, const uint64_t key)
{
    return void_manager->get(keyword)->copy(storage[key]);
}

void* body_data::deep_copy_index(const std::string& keyword, kvector<void*>& storage, const uint64_t index)
{
    return void_manager->get(keyword)->copy(storage[index]);
}*/

void body_data::mapinsert(const string& keyword, uint64_t key, lammps_type_ptr value)
{
    database[keyword].insert(key, value);
}

/*bool body_data::empty(const std::string &keyword)
{
    if (keyword == "Pair Coeffs" or keyword == "PairIJ Coeffs")
        return pair_coeffs.empty();
    else {
        try {
            return database.at(keyword).empty();
        }catch (std::exception& e){
            throw std::invalid_argument("The keyword is either currently not implemented or is incorrect");
        }
    }
}*/

/*
void body_data::move_body_data(body_data*)
{

}

void body_data::move(const std::string&, body_data*)
{

}*/

/*void body_data::copy_body_data(body_data* input)
{
    std::string body_keyword[12]= {"Atoms", "Masses", "Bond Coeffs", "Angle Coeffs",
                              "Dihedral Coeffs", "Improper Coeffs", "Pair Coeffs", "Velocities",
                              "Bonds", "Angles", "Dihedrals", "Impropers"
                            };
    for (int i = 0; i < 12; i++)
        delete_body_data(body_keyword[i]);

    std::vector<std::thread> t;
    for (int i = 0; i < 12; i++)
        t.push_back(std::thread(&body_data::copy, this, std::ref(body_keyword[i]), input));

    for (int i = 0; i < t.size(); i++)
        t[i].join();
}

void body_data::copy(const std::string & keyword, body_data* other)
{
    if (keyword != "Pair Coeffs" and keyword != "PairIJ Coeffs") {
        kmap<uint64_t, void*>& other_data = other->get_map(keyword);
        kmap<uint64_t, void*>& current_data = get_map(keyword);
        if (keyword == "Atoms") {
            std::string atom_style = other->get_atom_style();
            for (auto it = other_data.begin(); it != other_data.end(); it++) {
                void* value = void_manager->get(atom_style)->equals(it->second);
                current_data.insert(it->first, value);
            }
        }
        else {
            for (auto it = other_data.begin(); it != other_data.end(); it++) {
                void* value = void_manager->get(keyword)->equals(it->second);
                current_data.insert(it->first, value);
            }
        } //I think this will work with atom keyword
    }
    else {
        kvector<void*>& other_data = other->get_vector(keyword);
        kvector<void*>& current_data = get_vector(keyword);
        for (int i = 0; i < other_data.getsize(); i++) {
            void* value = void_manager->get(keyword)->equals(other_data[i]);
            current_data.push_back(value);
        }
    }
}

void body_data::deep_copy_body_data(body_data* input)
{
    std::string body_keyword[12]= {"Atoms", "Masses", "Bond Coeffs", "Angle Coeffs",
                              "Dihedral Coeffs", "Improper Coeffs", "Pair Coeffs", "Velocities",
                               "Bonds", "Angles", "Dihedrals", "Impropers"
                            };
    std::vector<std::thread> t;
    for (int i = 0; i < 12; i++)
        t.push_back(std::thread(&body_data::deep_copy, this, std::ref(body_keyword[i]), input));

    for (int i = 0; i < t.size(); i++)
        t[i].join();
}

void body_data::deep_copy(const std::string& keyword, body_data* other)
{
    if (keyword != "Pair Coeffs" and keyword != "PairIJ Coeffs") {
        kmap<uint64_t, void*>& current_data = get_map(keyword);
        kmap<uint64_t, void*>& other_data = other->get_map(keyword);
        if (keyword == "Atoms") {
            std::string atom_style = other->get_atom_style();
            for (auto it = other_data.begin(); it != other_data.end(); it++) {
                void* val = void_manager->get(atom_style)->copy(it->second);
                current_data.insert(it->first, val);
            }
        }
        else {
            for (auto it = other_data.begin(); it != other_data.end(); it++) {
                void* val = void_manager->get(keyword)->copy(it->second);
                current_data.insert(it->first, val);
            }
        }
    }
    else {
        kvector<void*>& current_data = get_vector(keyword);
        kvector<void*>& other_data = other->get_vector(keyword);
        for (int i = 0; i < other_data.getsize(); i++) {
            void* val = void_manager->get(keyword)->copy(other_data[i]);
            current_data.push_back(val);
        }
    }
}*/

kmap<uint64_t, lammps_type_ptr>& body_data::get_map(const std::string& keyword)
{
    try {
        return database.at(keyword);
    }
    catch (std::exception& e) {
        throw std::invalid_argument("The keyword, " + keyword +
                                    " is not in the data map either because its not implemented or incorrect");
    }
}

const string& body_data::get_atom_style()
{
    return atom_style;
}

void body_data::set_atom_style(const string& style)
{
    atom_style = style;
}

/*bool body_data::vector_property(const std::string& property_name)
{
    return (vector_properties.find(property_name) != vector_properties.end());
}

void body_data::join(std::vector<body_data*> data)
{

}

void body_data::add_body_data(body_data* input)
{

}

void body_data::add(std::vector<std::vector<std::string> >& info, const std::string& keyword)
{

}

void body_data::add(kmap<uint64_t, void*>& info, const std::string& keyword)
{

}

void body_data::add(kvector<void*>& info, const std::string& keyword)
{

}

void body_data::extract(body_data* input, const std::string& property, const uint64_t value, const int threads)
{
    std::unordered_set<uint64_t> keys = function_object::extract_atoms() (input, this, property, value, threads);
    function_object::extract_coeficients() (input, this);
    function_object::extract_velocities() (input, this, keys);
    function_object::extract_connections() (input, this, keys, threads); //is bugged
}

void body_data::extract(body_data* input, const std::string& property, const double value, const int threads)
{
    std::unordered_set<uint64_t> keys = function_object::extract_atoms() (input, this, property, value, threads);
    function_object::extract_coeficients() (input, this);
    function_object::extract_velocities() (input, this, keys);
    function_object::extract_connections() (input, this, keys, threads);
}*/

/*
std::unordered_set<uint64_t> body_data::find_set(std::string&, std::string&, uint64_t, int)
{

}

std::unordered_set<uint64_t> body_data::find_set(std::string&, std::string&, int64_t, int)
{

}

std::unordered_set<uint64_t> body_data::find_set(std::string&, std::string&, double, int)
{

}

kmap<uint64_t, void*> body_data::find_map(std::string&, std::string&, uint64_t, int)
{

}

kmap<uint64_t, void*> body_data::find_map(std::string&, std::string&, int64_t, int)
{

}

kmap<uint64_t, void*> body_data::find_map(std::string&, std::string&, double, int)
{

}

    //returns a vector of keys that match to one of a vector of values in the data set corresponding to keyword
std::unordered_set<uint64_t> body_data::search_set(std::string&, std::string&, std::unordered_set<uint64_t>&, int)
{

}

std::unordered_set<uint64_t> body_data::search_set(std::string&, std::string&, std::unordered_set<int64_t>&, int)
{

}

std::unordered_set<uint64_t> body_data::search_set(std::string&, std::string&, std::unordered_set<double>&, int)
{

}


kmap<uint64_t, void*> body_data::search_map(std::string&, std::string&, std::unordered_set<uint64_t>&, int)
{

}

kmap<uint64_t, void*> body_data::search_map(std::string&, std::string&, std::unordered_set<int64_t>&, int)
{

}

kmap<uint64_t, void*> body_data::search_map(std::string&, std::string&, std::unordered_set<double>&, int)
{

}

*/
