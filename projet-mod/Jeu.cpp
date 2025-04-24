#include "doctest.h"
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
    Ensemble identifiant = population.getIds();
    while(identifiant.cardinal() != 0) {
        int id = identifiant.tire();
        const Animal& animal = population.get(id);
        Coord c = animal.getCoord();
        if (grille.getCase(c) != id) {
            throw runtime_error("L'animal avec l'ID " + to_string(id) + " n'est pas à la bonne position.");
        }
    }
}


Ensemble Jeu::voisinsVides(Coord Case) const {
    Ensemble res;
    Ensemble voisins = Case.voisines();
    while(voisins.cardinal() != 0) {
        Coord temp = voisins.tire();
        if (grille.CaseVide(temp)) res.ajoute(temp.toInt());
    }
    return res;
}


Ensemble Jeu::voisinsEspece(Coord Case, Espece espece) const{
    Ensemble res;
    Ensemble voisins = Case.voisines();
    while(voisins.cardinal() != 0) {
        Coord temp = voisins.tire();
        int id = grille.getCase(temp);
        if (id != -1) {
            if(population.get(id).getEspece() == espece) {
                res.ajoute(temp.toInt());
            }
        }
    }
    return res;
}


void Jeu::Coherence() const {
    for (int y = 0; y < TAILLEGRILLE; y++) {
        for (int x = 0; x < TAILLEGRILLE; x++) {
            Coord Case = Coord {y,x};
            if (!grille.CaseVide(Case)) {
                int id = grille.getCase(Case);
                try {
                    population.get(id);
                } catch (const runtime_error ) {
                    throw runtime_error("L'animal de coordonnées (" + to_string(Case.getLigne()) + ", " + to_string(Case.getColonne()) + "), pour l'ID " + to_string(id) + " n'existe pas dans population.");
                }
            }
        }
    }
    Ensemble indices = population.getIds();
    while(indices.cardinal() != 0) {
        int temp = indices.tire();
        Animal actu = population.get(temp);
        Coord c = actu.getCoord();
        if (grille.CaseVide(c)) {
            throw runtime_error("La case de coordonnées (" + to_string(c.getLigne()) + ", " + to_string(c.getColonne()) + ") est vide alors qu'elle devrait contenir l'Animal d'id :" + to_string(temp));
        }
    }
}


void Jeu::DeplaceAnimal(Animal &animal) {
    Coord c = animal.getCoord();
    int id = animal.getId();
    Ensemble libre;
    if(animal.getEspece() == Espece::Lapin) {
        libre = voisinsVides(c);
    }
    else {
        libre = voisinsEspece(c, Espece::Lapin);
        if (libre.cardinal() == 0) libre = voisinsVides(c);
        else animal.mange();
        animal.jeune();
    }
    int temp = libre.tire();
    Coord case_nouvelle = Coord {temp};
    grille.VideCase(c);
    grille.setCase(case_nouvelle, id);
    animal.setCoord(case_nouvelle);
    Coherence();
}




