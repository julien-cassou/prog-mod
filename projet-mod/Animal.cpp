#include "coord.hpp"
#include "doctest.h"
#include "Animal.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <array>
using namespace std;


        // Espece

ostream& operator<<(ostream& out, Espece espece) {
    switch(espece) {
        case Espece::Renard: out << "Renard"; break;
        case Espece::Lapin: out << "Lapin"; break;
        default: throw runtime_error("espèce non reconnué");
    }
    return out;
}

        // Animal

<<<<<<< Updated upstream
Animal::Animal() : id{-1}, espece{Espece::Lapin}, coord{}, food{0} {};

=======
>>>>>>> Stashed changes
Animal::Animal(int id, Espece espece, Coord coord) : id{id} , espece{espece}, coord{coord}, food{FoodInit} {};


int Animal::getId() const {
    return id;
}


Coord Animal::getCoord() const {
    return coord;
}

void Animal::setCoord(Coord c) {
    coord = c;
}

Espece Animal::getEspece() const {
    return espece;
}


ostream& Animal::affiche(ostream &out) const {
    out << "Animal: " << id << ", " << espece << ", " << coord;
    if (espece == Espece::Renard ) {
        out << ", " << food;
    } 
    return out;
}

bool Animal::estMort() const {
    if (espece == Espece::Renard) {
        if (food <= 0) {
            return true;
        }
    }
    return false;
}  

void Animal::jeune() {
    if (espece == Espece::Lapin) {
        throw runtime_error("Un lapin mange tous le temps de l'herbe");
    }
    else {
        food -= 1;
    }
}



bool Animal::seReproduit(int nbVoisin) const {
    if (espece == Espece::Renard and food >= FoodReprod) {
        return (static_cast<double>(rand()) / RAND_MAX) < ProBirthRenard; // Vérifie si la reproduction réussit
    }
    else if (nbVoisin >= MinFreeBirthLapin) {
        return (static_cast<double>(rand()) / RAND_MAX) < ProBirthLapin; // Vérifie si la reproduction réussit
    }
    return false;
}

void Animal::mange() {
    if (espece == Espece::Lapin) {
        throw runtime_error("Un lapin ne mange que de l'herbe");
    }
    else if (food <= 5) {
        food += FoodLapin;
    }
    else {
        food = MaxFood;
    }
}




ostream& operator<<(ostream& out, Animal animal) {
    animal.affiche(out);
    return out;
}

        // Population

<<<<<<< Updated upstream
Population::Population() {
    // for (int i = 0; i < MAXCARD; i++) {
    //     animaux[i] = Animal();
    // }
=======
Population::Population() : id_dispo() {
>>>>>>> Stashed changes
    for (int i = 0; i < MAXCARD; i++) {
        id_reserve[i] = false;
        id_dispo.push_back(i + 1);
    }
    animaux.clear();
}


Animal Population::get(int id) const {
    for (size_t i = 0; i < animaux.size(); i++) {
        if (animaux[i].getId() == id) { 
            return animaux[i];
        }
    }
    throw runtime_error("L'animal n'existe pas");
}


Ensemble Population::getIds() const {
	Ensemble indice;
	for(size_t i = 0; i < animaux.size(); i++) {
		indice.ajoute(animaux[i].getId());
	}
	return indice;
}


int Population::reserve() {
<<<<<<< Updated upstream
    int id = id_dispo[id_dispo.size() - 1];
    id_dispo.pop_back(id);
    id_reserve[id] = true;
    animaux[i] = Animal();
=======
    if (id_dispo.empty()) {
        throw runtime_error("Aucun ID disponible pour la réservation");
    }
    int id = id_dispo.back();
    id_dispo.pop_back();
    id_reserve[id -1] = true;
    return id;
>>>>>>> Stashed changes
}

void Population::set(Animal &animal) {
    if (id_dispo.empty()) {
        throw runtime_error("Aucun ID disponible");
    }
    int id = reserve();
    Coord c = animal.getCoord();
    Espece e = animal.getEspece();
    animal = Animal(id, e, c);
    animaux.push_back(animal);
}

<<<<<<< Updated upstream
void supprime(int id) {
    id_dispo.push_back(id);
    id_reserve[id] = false;
    animaux[id] = Animal();
=======
void Population::supprime(int id) {
    for (size_t i = 0; i < animaux.size(); i++) {
		if (animaux[i].getId() == id) {
            id_dispo.push_back(id);
			animaux.erase(animaux.begin() + i);
            id_reserve[id - 1] = false;
			return;
		}
	} throw runtime_error("Cette ID n'existe pas");
}

bool Population::estPresent(int id) const {
    for (size_t i = 0; i < animaux.size(); i++) {
        if (animaux[i].getId() == id) {
            return true;
        }
    }
    return false;
>>>>>>> Stashed changes
}

