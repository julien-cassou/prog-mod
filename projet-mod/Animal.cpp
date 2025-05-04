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

// implémenté par Julien Cassou
ostream& operator<<(ostream& out, Espece espece) {
    switch(espece) {
        case Espece::Renard: out << "Renard"; break;
        case Espece::Lapin: out << "Lapin"; break;
        default: throw runtime_error("espèce non reconnué");
    }
    return out;
}

        // Animal

// implémenté par Julien Cassou
Animal::Animal(int id, Espece espece, Coord coord, int food, int age) : id{id}, espece{espece}, coord{coord}, food{food}, age{age} {};

// implémenté par Julien Cassou
int Animal::getId() const {
    return id;
}

// implémenté par Julien Cassou
Coord Animal::getCoord() const {
    return coord;
}

// implémenté par Julien Cassou
void Animal::setCoord(Coord c) {
    coord = c;
}

// implémenté par Julien Cassou
Espece Animal::getEspece() const {
    return espece;
}

// implémenté par Julien Cassou
int Animal::getAge() const {
    return age;
}

// implémenté par Julien Cassou
ostream& Animal::affiche(ostream &out) const {
    out << "Animal: " << id << ", " << espece << ", " << coord << ", " << age;
    if (espece == Espece::Renard ) {
        out << ", " << food;
    } 
    return out;
}

// implémenté par Julien Cassou
void Animal::vieilli() {
    age++;
}

// implémenté par Julien Cassou
bool Animal::estMort() const {
    double prob = static_cast<double>(rand()) / RAND_MAX;
    if (espece == Espece::Renard) {
        return (food <= 0) or (age >= 5 && prob < 0.4) or (age >= 15);
    }
    return (age >=  8);
}  
    
// implémenté par Julien Cassou
void Animal::jeune() {
    if (espece == Espece::Lapin) {
        throw runtime_error("Un lapin mange tous le temps de l'herbe");
    }
    else {
        food -= 1;
    }
}

// implémenté par Julien Cassou
bool Animal::seReproduit(int nbVoisin, const Param &p) const {
    if ((espece == Espece::Renard) and (food >= FoodReprod)) {
        return (static_cast<double>(rand()) / RAND_MAX) < p.ProBirthRenard; // Vérifie si la reproduction réussit
    }
    else if (espece == Espece::Lapin and nbVoisin >= MinFreeBirthLapin) {
        return (static_cast<double>(rand()) / RAND_MAX) < p.ProBirthLapin; // Vérifie si la reproduction réussit
    }
    else {
        return false;
    }
}

// implémenté par Julien Cassou
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



// implémenté par Julien Cassou
ostream& operator<<(ostream& out, Animal animal) {
    animal.affiche(out);
    return out;
}

        // Population

// implémenté par Julien Cassou
Population::Population() : id_dispo() {
    for (int i = 0; i < MAXCARD; i++) {
        id_reserve[i] = false;
        id_dispo.push_back(i + 1);
    }
    animaux.clear();
}

// implémenté par Julien Cassou
Animal Population::get(int id) const {
    for (size_t i = 0; i < animaux.size(); i++) {
        if (animaux[i].getId() == id) { 
            return animaux[i];
        }
    }
    throw runtime_error("L'animal n'existe pas");
}

// implémenté par Julien Cassou
Ensemble Population::getIds() const {
	Ensemble indice;
	for(size_t i = 0; i < animaux.size(); i++) {
		indice.ajoute(animaux[i].getId());
	}
	return indice;
}

// implémenté par Julien Cassou
int Population::reserve() {
    if (id_dispo.empty()) {
        throw runtime_error("Aucun ID disponible pour la réservation");
    }
    int id = id_dispo.back();
    id_dispo.pop_back();
    id_reserve[id -1] = true;
    return id;
}

// implémenté par Julien Cassou
void Population::set(Animal &animal) {
    if (id_dispo.empty()) {
        throw runtime_error("Aucun ID disponible");
    }
    int id = reserve();
    Coord c = animal.getCoord();
    Espece e = animal.getEspece();
    int f = animal.getFood();
    int a = animal.getAge();
    animal = Animal(id, e, c, f, a);
    animaux.push_back(animal);
}

// implémenté par Julien Cassou
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

/** fonction permettant de vérifiant la présence d'un animal dans une population
 * @param entier id désignant l'identifiant de l'animal
 * @return vrai si il est dans la population, sinon non
 */
// implémenté par Julien Cassou
bool Population::estPresent(int id) const {
    for (size_t i = 0; i < animaux.size(); i++) {
        if (animaux[i].getId() == id) {
            return true;
        }
    }
    return false;
}

