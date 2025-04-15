//
//  coord.hpp
//  coordonées
//
//  Created by Lucia Casalta on 02/04/2025.
//

#ifndef COORD_HPP
#define COORD_HPP
#include <stdexcept>
#include <ostream>
using namespace std;


    // Julien

// Ex 3

const int MAXCARD = 1600;

class Ensemble {
    private:
    int t[MAXCARD];
    int card;
    public:
    // constructeurs
    Ensemble();
    // méthodes
    int cardinal() const;
    bool estVide() const;
    void ajoute(int entier);
    int tire();
    void affiche(ostream& out) const;
    void nouvelle_ensemble(int taille);
    // opérateur
    friend ostream &operator<<(ostream& out, const Ensemble& e);
};


const int TAILLEGRILLE = 40;

// TD / Cours
    // Julien

//declaration de la class pour position dans une grille
class Coord {
    private:
    int ligne;
    int colonne;
    public:
    //constructeur : interdit les coordonnées hors de la grille
    Coord(int l, int c);
    Coord(int entier);
    //méthodes
    int getLigne() const;
    int getColonne() const;
    Ensemble voisines() const;
    // opérateur
    friend ostream &operator<<(ostream& os, const Coord& c);
};

enum class Espece(Lapin, Renard);

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
        // Animal();
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
        void set(int id; Animal animal);
        void supprime(int id);
    private:
        array<Animal,MAX> animaux;
        array<bool,MAX> id-reserve;
};

class Grille {
    public:
        // Constructeur;
        Grille();
        // Méthodes
        bool CaseVide(Coord coodonnées) const;
        int getCase(Coord coordonnées) const;
        void VideCase(Coord coordonnées);
        void setCase(Coord coordonnées, int id);
    private:
        vector<vector<Coord>> Grille;
};

class Jeu {
    public:
        Animal ajouteAnimal();
    private:
        Population population;
        Grille grille;
}
#endif // COORD_HPP