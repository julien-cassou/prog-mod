#include "coord.hpp"
#include "doctest.h"
#include "Animal.hpp"
#include "Jeu.hpp"
#include <stdexcept>
#include <sstream>
#include <vector>
#include <array>
using namespace std;

        // Grille

Grille::Grille() {
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            grille[i][j] = -1;
        }
    }
}

bool Grille::CaseVide(Coord coordonnées) const {
    return (grille[coordonnées.getLigne()][coordonnées.getColonne()] == -1);
}

int Grille::getCase(Coord coordonnées) const{
    if(CaseVide(coordonnées)) throw runtime_error("Il n'y a rien à cette coordonnées");
    return (grille[coordonnées.getLigne()][coordonnées.getColonne()]);
}

void Grille::VideCase(Coord coordonnées) {
    grille[coordonnées.getLigne()][coordonnées.getColonne()] = -1;
}

void Grille::setCase(Coord coordonnées, int id) {
    grille[coordonnées.getLigne()][coordonnées.getColonne()] = id;
}


        // Animal

void Jeu::ajouteAnimal(Espece espece, Coord c) {
    int id = population.reserve();
    Animal temp = Animal {id, espece, c};
    population.set(id, temp);
    grille.setCase(c, id);
}