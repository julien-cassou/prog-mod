#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <stdexcept>
#include <ostream>
#include <vector>
#include <array>
#include "param.hpp"
using namespace std;

enum class Espece {Lapin, Renard};

// const float ProBirthLapin = 0.20;
const int MinFreeBirthLapin = 5;
// const float ProBirthRenard = 0.10;

const int FoodInit = 5;
const int FoodLapin = 5;
const int FoodReprod = 8;
const int MaxFood = 10;
const int AgeInit = 0;

class Animal {
    public:
        // Constructeurs
        Animal(int id, Espece espece, Coord coord, int food, int age);
        // accesseurs
        int getId() const;
        Coord getCoord() const;
        void setCoord(Coord c);
        Espece getEspece() const;
        ostream& affiche(ostream &out) const;
        int getAge() const;
        // predicats
        bool estMort() const;
        bool seReproduit(int nbvoisin, const Param &p) const;
        // modification
        void mange();
        void jeune();
        void vieilli();
        // débogage
        int getFood() const { return food; }
    private:
        int id;
        Espece espece;
        Coord coord;
        int food;
        int age;
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
        void set(Animal &animal);
        void supprime(int id);
        // débogage & tests
        bool estPresent(int id) const;  
        const vector<Animal>& getAnimaux() const { return animaux; }
    private:
        vector<Animal> animaux;
        array<bool,MAXCARD> id_reserve;
        vector<int> id_dispo;
};
#endif