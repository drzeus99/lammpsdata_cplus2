#ifndef LMPSDATA_H
#define LMPSDATA_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "header_data.h"
#include "body_data.h"
#include <list>
namespace lmpsdata {
class Lmpsdata: public header_data, public body_data
{
public:
    //members
    std::list<std::string> header_keywords;
    std::list<std::string> body_keywords;
    //methods
    Lmpsdata(const std::string&, const std::string& ="");
    void read(const std::string&);
    void write(const std::string&, const std::string& ="");
private:
    //methods
    std::string readheader(std::ifstream &);
    void readbody(std::ifstream &, std::string&);
    void insertbody(const std::string&, std::string&);
    void writeheader(std::ofstream &, const std::string&);
    void writebody(std::ofstream &);
};
}

#endif // LMPSDATA_H
