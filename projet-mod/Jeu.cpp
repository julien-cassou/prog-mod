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

Jeu::Jeu(double probLapins, double probRenard) {
    for (int i = 0; i < TAILLEGRILLE; ++i) {
        for (int j = 0; j < TAILLEGRILLE; ++j) {
            double proba = static_cast<double>(rand()) / RAND_MAX;
            Coord c {i, j};
            if (proba < probLapins) {
                ajouteAnimal(Espece::Lapin, c);
            } else if (proba < probLapins + probRenard) {
                ajouteAnimal(Espece::Renard, c);
            } else {
                grille.setCase(c, -1);
            }
        }
    }
}


void Jeu::verifieGrille() const {
    for (int id = 0; id < population.size(); ++id) {
        const Animal& animal = population.get(id);
        Coord c = animal.getCoord();
        if (grille.getCase(c) != id) {
            throw runtime_error("L'animal avec l'ID " + to_string(id) + " n'est pas à la bonne position.");
        }
    }
}

Spécifiez et réalisez une méthode voisinsVides qui retourne l’ensemble des cases voi
sines vides d’une case.

Ensemble Jeu::voisinsVides(Coord case) const {
    Ensemble res;
    Enemble voisins = case.voisines();
    while(voisins.cardinal() != 0) {
        Coord temp = voisins.tire();
        if (grille.CaseVide(temp)) res.ajoute(temp.toInt());
    }
    return res;
}
