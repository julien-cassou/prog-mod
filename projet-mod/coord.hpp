#ifndef COORD_HPP
#define COORD_HPP
#include <stdexcept>
#include <ostream>
#include <vector>
#include <array>
using namespace std;

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
    int toInt();
    // opérateur
    friend ostream &operator<<(ostream& os, const Coord& c);
};

bool operator==(const Coord &c, const Coord &d);
bool operator!=(const Coord& c, const Coord&d);
#endif // COORD_HPP