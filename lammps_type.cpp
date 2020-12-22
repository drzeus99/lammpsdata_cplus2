#include "lammps_type.h"
using namespace lmpsdata;
using namespace std;
//constructor
lammps_type::lammps_type(const string& key)
{
    this->key = key;
    (*constructor_map)[key](this);
}

lammps_type::lammps_type(shared_ptr<lammps_type>& obj)
{
    key = obj->key;
    (*copier_map)[key](this, obj.get());
}

//destructor
lammps_type::~lammps_type()
{
    (*dest_map)[key](this);
}

//read/write
void lammps_type::read(string& line)
{
    (*reader_map)[key](this,line);
}

void lammps_type::write(ostream& os)
{
    (*writer_map)[key](this, os);
}

//property access
uint64_t& lammps_type::u_property(const string& property)
{
    pair<string, string> k_p = make_pair(key, property);
    try {
        return u_props.at(k_p)(this);
    } catch (out_of_range e) {
        throw invalid_argument("key-property pair (" + key + "," + property + ") doesn't exist for type uint64_t");
    }
}

double& lammps_type::d_property(const string& property)
{
    pair<string, string> k_p = make_pair(key, property);
    try {
        return d_props.at(k_p)(this);
    } catch (out_of_range e) {
        throw invalid_argument("key-property pair (" + key + "," + property + ") doesn't exist for type double");
    }
}

string& lammps_type::s_property(const string& property)
{
    pair<string, string> k_p = make_pair(key, property);
    try {
        return s_props.at(k_p)(this);
    } catch (out_of_range e) {
        throw invalid_argument("key-property pair (" + key + "," + property + ") doesn't exist for type string");
    }
}

valarray<uint64_t>& lammps_type::u_v_property(const string& property)
{
    pair<string, string> k_p = make_pair(key, property);
    try {
        return u_v_props.at(k_p)(this);
    } catch (out_of_range e) {
        throw invalid_argument("key-property pair (" + key + "," + property + ") doesn't exist for type valarray<uint64_t>");
    }
}

valarray<int64_t>& lammps_type::i_v_property(const string& property)
{
    pair<string, string> k_p = make_pair(key, property);
    try {
        return i_v_props.at(k_p)(this);
    } catch (out_of_range e) {
        throw invalid_argument("key-property pair (" + key + "," + property + ") doesn't exist for type valarray<int64_t>");
    }
}

valarray<double>& lammps_type::d_v_property(const string& property)
{
    pair<string, string> k_p = make_pair(key, property);
    try {
        return d_v_props.at(k_p)(this);
    } catch (out_of_range e) {
        throw invalid_argument("key-property pair (" + key + "," + property + ") doesn't exist for type valarray<unint64_t>");
    }
}

//static map initializers
map<string, lammps_type::type_creator>* lammps_type::initialize_constructors()
{
    map<string, type_creator>* result = new map<string, type_creator>();
    #define LAMMPS_TYPE_CONSTRUCTOR
    #define type_style(key, class, type)\
        (*result)[#key] = [](lammps_type* lt) {\
            lt->v.type = new class();\
            };
    #include "lammps_type.h"
    #undef type_style
    #undef LAMMPS_TYPE_CLASS
    return result;
}

map<string, lammps_type::type_copier>* lammps_type::initialize_copiers()
{
    map<string,type_copier>* result = new map<string,type_copier>();
    #define LAMMPS_TYPE_CONSTRUCTOR
    #define type_style(key, class, type)\
        (*result)[#key] = [](lammps_type* lt, lammps_type* obj) {\
            lt->v.type = (class*) obj->v.type->copy();\
        };
    #include "lammps_type.h"
    #undef type_style
    #undef LAMMPS_TYPE_CONSTRUCTOR
    return result;
}

map<string, lammps_type::type_dest>* lammps_type::init_dest()
{
    map<string, type_dest>* result = new map<string, type_dest>();
    #define LAMMPS_TYPE_CONSTRUCTOR
    #define type_style(key, class, type)\
        (*result)[#key] = [](lammps_type* lt) {\
            delete lt->v.type;\
        };
    #include "lammps_type.h"
    #undef type_style
    #undef LAMMPS_TYPE_CONSTRUCTOR
    return result;
}

map<string, lammps_type::type_reader>* lammps_type::initialize_readers()
{
    map<string, type_reader>* result = new map<string, type_reader>();
    #define LAMMPS_TYPE_INTERFACE
    #define lti(key, type)\
        (*result)[#key] = [](lammps_type* lt, string& line) {\
            lt->v.type->read(line);\
        };
    #include "lammps_type.h"
    #undef lti
    #undef LAMMPS_TYPE_INTERFACE
    return result;
}

map<string, lammps_type::type_writer>* lammps_type::initialize_writers()
{
    map<string, type_writer>* result = new map<string, type_writer>();
    #define LAMMPS_TYPE_INTERFACE
    #define lti(key, type)\
        (*result)[#key] = [](lammps_type* lt, ostream& os) {\
            lt->v.type->write(os);\
        };
    #include "lammps_type.h"
    #undef lti
    #undef LAMMPS_TYPE_INTERFACE
    return result;
}

map<pair<string, string>, lammps_type::u_prop> lammps_type::init_u_props()
{
    map<pair<string, string>, u_prop> result;
    #define U_PROPERTY
    #define prop(key, type, field) \
        result[make_pair(string(#key), string(#field))] = [] (lammps_type* lt) -> uint64_t& {\
            return lt->v.type->get_##field();\
        };
    #include "lammps_type.h"
    #undef prop
    #undef U_PROPERTY
    return result;
}

map<pair<string, string>, lammps_type::d_prop> lammps_type::init_d_props()
{
    map<pair<string, string>, d_prop> result;
    #define D_PROPERTY
    #define prop(key, type, field) \
        result[make_pair(string(#key), string(#field))] = [] (lammps_type* lt) -> double& {\
            return lt->v.type->get_##field();\
        };
    #include "lammps_type.h"
    #undef prop
    #undef D_PROPERTY
    return result;
}

map<pair<string, string>, lammps_type::s_prop> lammps_type::init_s_props()
{
    map<pair<string, string>, s_prop> result;
    #define S_PROPERTY
    #define prop(key, type, field) \
        result[make_pair(string(#key), string(#field))] = [] (lammps_type* lt) -> string& {\
            return lt->v.type->get_##field();\
        };
    #include "lammps_type.h"
    #undef prop
    #undef S_PROPERTY
    return result;
}

map<pair<string, string>, lammps_type::u_v_prop> lammps_type::init_u_v_props()
{
    map<pair<string, string>, u_v_prop> result;
    #define U_V_PROPERTY
    #define prop(key, type, field) \
        result[make_pair(string(#key), string(#field))] = [] (lammps_type* lt) -> valarray<uint64_t>& {\
            return lt->v.type->get_##field();\
        };
    #include "lammps_type.h"
    #undef prop
    #undef U_V_PROPERTY
    return result;
}

map<pair<string, string>, lammps_type::i_v_prop> lammps_type::init_i_v_props()
{
    map<pair<string, string>, i_v_prop> result;
    #define I_V_PROPERTY
    #define prop(key, type, field) \
        result[make_pair(string(#key), string(#field))] = [] (lammps_type* lt) -> valarray<int64_t>& {\
            return lt->v.type->get_##field();\
        };
    #include "lammps_type.h"
    #undef prop
    #undef I_V_PROPERTY
    return result;
}

map<pair<string, string>, lammps_type::d_v_prop> lammps_type::init_d_v_props()
{
    map<pair<string, string>, d_v_prop> result;
    #define D_V_PROPERTY
    #define prop(key, type, field) \
        result[make_pair(string(#key), string(#field))] = [] (lammps_type* lt) -> valarray<double>& {\
            return lt->v.type->get_##field();\
        };
    #include "lammps_type.h"
    #undef prop
    #undef D_V_PROPERTY
    return result;
}

//static initializers
map<string, lammps_type::type_creator>* lammps_type::constructor_map = lammps_type::initialize_constructors();
map<string, lammps_type::type_copier>* lammps_type::copier_map = lammps_type::initialize_copiers();
map<string, lammps_type::type_dest>* lammps_type::dest_map = lammps_type::init_dest();
map<string, lammps_type::type_reader>* lammps_type::reader_map = lammps_type::initialize_readers();
map<string, lammps_type::type_writer>* lammps_type::writer_map = lammps_type::initialize_writers();
map<pair<string, string>, lammps_type::u_prop> lammps_type::u_props = lammps_type::init_u_props();
map<pair<string, string>, lammps_type::d_prop> lammps_type::d_props = lammps_type::init_d_props();
map<pair<string, string>, lammps_type::s_prop> lammps_type::s_props = lammps_type::init_s_props();
map<pair<string, string>, lammps_type::u_v_prop> lammps_type::u_v_props = lammps_type::init_u_v_props();
map<pair<string, string>, lammps_type::i_v_prop> lammps_type::i_v_props = lammps_type::init_i_v_props();
map<pair<string, string>, lammps_type::d_v_prop> lammps_type::d_v_props = lammps_type::init_d_v_props();
