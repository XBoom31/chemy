
#ifndef UTILS_H
#define UTILS_H

//"AtomicNumber","Symbol","Name","AtomicMass","CPKHexColor","ElectronConfiguration",
//"Electronegativity","AtomicRadius","IonizationEnergy","ElectronAffinity",
//"OxidationStates","StandardState","MeltingPoint","BoilingPoint","Density",
//"GroupBlock","YearDiscovered"
#include <string>
#include <QResource>

const std::string elem_cu_rosu[] = {"H",
    "He","N","O","F","Ne","Cl","Ar","Kr",
    "Xe", "Rn"};

const std::string elem_cu_verde[] = {"Br", "Hg"};

struct element{
    int natomic;
    std::string sym;
    std::string nume;
    float atomic_mass;
    std::string color;
    std::string electron_conf;
    float electron_negativity;
    float rad_atom;
    float ionization_energy;
    float electron_affinity;
    std::string oxidation_states;
    std::string standard_state;
    float melting_point;
    float boiling_point;
    float density;
	std::string group_block;
    int year;
};
#endif // UTILS_H
