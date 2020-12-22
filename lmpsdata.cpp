#include "lmpsdata.h"
#include <iostream>
using namespace lmpsdata;
using namespace std;

//public methods
Lmpsdata::Lmpsdata(const string& atomstyle, const string& file)
{
    set_atom_style(atomstyle);
    read(file);
}

void Lmpsdata::read(const string& file)
{
   if (file == "" )
        return;
    ifstream myfile;
    myfile.open(file);
    string line = readheader(myfile);
    readbody(myfile, line);
}

void Lmpsdata::write(const string& file, const string& comment)
{
  ofstream myfile;
  myfile.open(file);
  myfile.precision(16);
  writeheader(myfile, comment);
  myfile << "\n";
  writebody(myfile);
  myfile.close();
}

//private methods
std::string Lmpsdata::readheader(ifstream &file)
{
    cout<<"reading header data"<<std::endl;
    string line, keyword;
    bool keyword_test;
    getline(file,line);
    while (file.good()){
        getline(file,line);
        keyword = check_header_keyword(line, keyword_test);
        if (keyword_test) {
            header_data::read(line, keyword);
            header_keywords.push_back(keyword);
        }
        else if (line == "") {
            continue;
        }
        else {
            return line;
        }
    }
    return line;
}

void Lmpsdata::readbody(ifstream &file, string& line) //!fix the below code Also look into splitting steps into this algorithm into separate methods
{
    std::cout << "reading body data\n";
    int blanklines = 0;
    std::string keyword = check_body_keyword(line);
    if (keyword != "")
        body_keywords.push_back(keyword);
    else
        throw std::ios_base::failure("the line " + line + " did not contain a valid keyword");
    while (file.good()) {
        getline(file, line);
        //!std::cout << "the line is " << line << std::endl;
        if (blanklines <= 1) {
            if (line != "") {
                insertbody(keyword, line);
            }
            else {
                blanklines += 1;
                //!std::cout << "updating blank lines to "  <<  blanklines << std::endl;
            }

        } else {
            keyword = check_body_keyword(line);
            if (keyword != "") {
                body_keywords.push_back(keyword);
                blanklines = 0;
            }
            else
                throw std::ios_base::failure("the line " + line + " did not contain a valid keyword");
        }
        //!std::cout << "the keyword is " << keyword << std::endl;
    }
}

void Lmpsdata::insertbody(const string& keyword, string& line)
{
    string::size_type st = 0;
    uint64_t key = stoull(line, &st);
    line = line.substr(st);
    auto val = (keyword == "Atoms") ? lammps_type_ptr(new lammps_type(get_atom_style())) : lammps_type_ptr(new lammps_type(keyword));
    val->read(line);
    mapinsert(keyword, key, val);
}

void Lmpsdata::writeheader(ofstream &file, const string& comment)
{
    cout << "writing header data \n";
    file << comment << endl;
    for (auto it = header_keywords.begin(); it != header_keywords.end(); it++)
        header_data::write(file, *it);
}

void Lmpsdata::writebody(ofstream &file)
{
    cout << "writing body data \n";
    for (string keyword: body_keywords) {
        cout << "writing keyword " << keyword << endl;
        file << keyword << "\n\n";
        kmap<uint64_t, lammps_type_ptr>& data = get_map(keyword);
        for (auto slot = data.begin(); slot != data.end(); slot++) {
            file << slot->first << " ";
            slot->second->write(file);
        }
        file << "\n";
    }
}
