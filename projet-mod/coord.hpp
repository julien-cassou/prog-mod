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

const int TAILLEGRILLE = 40;

//declaration de la class pour position dans une grille
class Coord {
private:
    int ligne;
    int colonne;
    
public:
    //constructeur : interdit les coordonnées hors de la grille
    Coord(int l, int c);
    Coord(int entier);
    //accesseurs
    int getLigne() const;
    int getColonne() const;
};
#endif // COORD_HPP


//question 7
ostream& operator<<(ostream& os, const Coord& c);
