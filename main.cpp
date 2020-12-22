#include <iostream>
#include "lammps_type.h"
#include "lmpsdata.h"
#include <array>
using namespace lmpsdata;
using namespace std;

int main()
{
    auto p1 = lammps_type_ptr(new lammps_type("atom"));
    auto& pos = atom_field(p1, position);
    pos[0] = .03;
    pos[1] = .02;
    cout << atom_field(p1, position)[0] << endl;
    atom_field(p1, charge) = .3;
    atom_field(p1, molecule) = 22;
    cout << p1->d_property("charge") << " " << p1->u_property("molecule") << endl;
    auto p2 = lammps_type_ptr(new lammps_type("Bonds"));
    auto p3 = lammps_type_ptr(new lammps_type("Angles"));
    auto p4 = lammps_type_ptr(new lammps_type("Impropers"));
    cout << "the sizes of atom ids are: " << abd_field(p2, atom_ids).size() << " ";
    cout  << abd_field(p3, atom_ids).size() << " " << abd_field(p4, atom_ids).size() << endl;
    abd_field(p3, type) = 15;
    cout << "the type is: " << p3->u_property("type") << endl;

    Lmpsdata* data = new Lmpsdata("full", "pmma98compositedata.initeq");
    //test getting
    //test writing
    array<string,11> keywords = {"Atoms", "Masses", "Bond Coeffs", "Angle Coeffs",
                              "Dihedral Coeffs", "Improper Coeffs", "Velocities",
                              "Bonds", "Angles", "Dihedrals", "Impropers"
                              };
    for (string keyword: keywords) {
        cout << keyword << " "<< data->get_map(keyword).entry_number() << endl;
    }

    data->write("file_test.txt");
    delete data;
    return 0;
}
