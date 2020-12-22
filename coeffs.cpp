#include "coeffs.h"
using namespace lmpsdata;
using namespace std;

void Coeffs::read(string& line)
{
    read_info(line);
}

void Coeffs::write(ostream& file)
{
    write_info(file);
    file << "\n";
}

void Coeffs::read_info(std::string& line)
{
    info = line;
}

void Coeffs::write_info(std::ostream& file)
{
    file << info << " ";
}

string& Coeffs::get_info()
{
    return info;
}

bool Coeffs::atom_type_match(vector<uint64_t>& input_types)
{
    if (input_types.size() != atom_types[0].size())
        test_result = false;
    else {
        for (unsigned i = 0; i < atom_types.size(); i++) {
            for (unsigned j = 0; j < input_types.size(); j++) {
                if (atom_types[i].find(input_types[j]) == atom_types[i].end())
                    break;
                else {
                    if (j < (input_types.size()-1) )
                        continue;
                    else {
                        test_result = true;
                        goto finish;
                    }
                }
            }
        }
        test_result = false;
    }
    finish:
    return test_result;
}
