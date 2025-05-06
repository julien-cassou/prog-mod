#ifndef PARAM_HPP
#define PARAM_HPP
#include "coord.hpp"
using namespace std;

struct Param {
    float ProBirthLapin, ProBirthRenard, ProbSpawnLapins, ProbSpawnRenards;
    int NbTours;

    // Constructeur par défault pour garder les valeurs initiales
    Param() : ProBirthLapin(0.20), ProBirthRenard(0.10), ProbSpawnLapins(0.20), ProbSpawnRenards(0.07), NbTours(50) {};
};
#endif