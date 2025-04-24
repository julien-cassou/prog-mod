#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <stdexcept>
#include <ostream>
#include <vector>
#include <array>
#include "coord.hpp"
using namespace std;

enum class Espece {Lapin, Renard};

const float ProBirthLapin = 0.30;
const int MinFreeBirthLapin = 4;
const float ProBirthRenard = 0.05;

const int FoodInit = 5;
const int FoodLapin = 5;
const int FoodReprod = 8;
const int MaxFood = 10;

class Animal {
    public:
        // Constructeurs
        Animal();
        Animal(int id, Espece espece, Coord coord);
        // accesseurs
        int getId() const;
        Coord getCoord() const;
        void setCoord(Coord c);
        Espece getEspece() const;
        ostream& affiche(ostream &out) const;
        // predicats
        bool estMort() const;
        bool seReproduit(int nbvoisin) const;
        // modification
        void mange();
        void jeune();
    private:
        int id;
        Espece espece;
        Coord coord;
        int food;
};

ostream& operator<<(ostream& out, Espece espece);
ostream& operator<<(ostream& out, Animal animal);

class Population {
    public:
        // Constructeur
        Population();
        // Méthodes
        Animal get(int id) const;
        Ensemble getIds() const;
        int reserve();
        void set(int id, Animal animal);
        void supprime(int id);
    private:
        array<Animal,MAXCARD> animaux;
        array<bool,MAXCARD> id_reserve;
        vector<int> id_dispo;
};

#endif