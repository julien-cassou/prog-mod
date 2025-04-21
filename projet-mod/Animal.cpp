#include "coord.hpp"
#include "doctest.h"
#include "Animal.hpp"
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

TEST_CASE("affichage espèce") {
    ostringstream out;
    out << Espece::Renard;
    CHECK(out.str() == "Renard");
    ostringstream os;
    os << Espece::Lapin;
    CHECK(os.str() == "Lapin");
}

        // Animal

Animal::Animal() : id{-1}, espece{Espece::Lapin}, coord{}, food{0} {};

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

TEST_CASE("constructeur & accesseurs") {
    Animal a = {23, Espece::Renard, Coord (1,2)};
    CHECK(a.getId() == 23);
    CHECK(a.getCoord() == Coord (1,2));
    a.setCoord(Coord (3,4));
    CHECK(a.getCoord() == Coord (3,4));
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
        if (food == 0) {
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

TEST_CASE("estMort & jeune") {
    Animal b = {3, Espece::Renard, Coord (6,13)};
    CHECK_FALSE(b.estMort());
    for(int i = 1; i <= 5; i++) { b.jeune();}
    CHECK(b.estMort());
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

TEST_CASE("mange") {
    Animal b = {3, Espece::Renard, Coord (6,13)};
    for(int i = 1; i <= 5; i++) { b.jeune();}
    b.mange();
    CHECK_FALSE(b.estMort());
    Animal a = {2, Espece::Lapin, Coord (5,13)};
    CHECK_THROWS_AS(a.mange(), runtime_error);
}


ostream& operator<<(ostream& out, Animal animal) {
    animal.affiche(out);
    return out;
}

TEST_CASE("affichage Animal") {
    Animal a = {2, Espece::Lapin, Coord (5,13)};
    ostringstream os;
    os << a;
    CHECK(os.str() == "Animal: 2, Lapin, (5,13)");
    Animal b = {3, Espece::Renard, Coord (6,13)};
    ostringstream oss;
    oss << b;
    CHECK(oss.str() == "Animal: 3, Renard, (6,13), 5");
}

        // Population

Population::Population() {
    // for (int i = 0; i < MAXCARD; i++) {
    //     animaux[i] = Animal();
    // }
    for (int i = 0; i < MAXCARD; i++) {
        id_reserve[i] = false;
    }
    for (int i = 0; i < MAXCARD; i++) {
        id_dispo[i] = i;
    }
}


Animal Population::get(int id) const {
    for (int i = 0; i < MAXCARD; i++) {
        if (id_reserve[i] == id) {
            for (int j = 0; j < MAXCARD; j++) {
                if (animaux[j].getId() == id) { 
                    return animaux[j];
                }
            }
        }
    }
    throw runtime_error("L'animal n'existe pas");
}


Ensemble Population::getIds() const {
    Ensemble indice;
    for (const auto& animal: animaux) {
        int temp = animal.getId();
        if (temp != -1) indice.ajoute(temp);
    }
    return indice;
}


int Population::reserve() {
    int id = id_dispo[id_dispo.size() - 1];
    id_dispo.pop_back(id);
    id_reserve[id] = true;
    animaux[i] = Animal();
}

void Population::set(int id, Animal animal) {
    animaux[id] = animal;
}

void supprime(int id) {
    id_dispo.push_back(id);
    id_reserve[id] = false;
    animaux[id] = Animal();
}

