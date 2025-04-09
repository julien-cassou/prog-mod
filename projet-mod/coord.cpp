//
//  coord.cpp
//  coordonées
//
//  Created by Lucia Casalta on 02/04/2025.
//

#include "coord.hpp"
#include "doctest.h"
#include <stdexcept>
#include <sstream>
using namespace std;

//constructeur
//crée une coordonnée valide,lance une exception si hors de la grille
Coord::Coord(int l, int c) {
    if (l < 0 || l >= TAILLEGRILLE || c < 0 || c >= TAILLEGRILLE) {
        throw out_of_range("en dehors de la grille");
    }
    ligne = l;
    colonne = c;
}

//accesseur ligne,question 5(getters)
int Coord::getLigne() const {
    return ligne;
}

//accesseur colonne
int Coord::getColonne() const {
    return colonne;
}

//TESTS UNITAIRES
TEST_CASE("construction valide") {
    Coord c(10, 15);
    CHECK(c.getLigne() == 10);
    CHECK(c.getColonne() == 15);
}

TEST_CASE( "ligne hors borne") {
    CHECK_THROWS_AS(Coord(-1, 10), out_of_range);
    CHECK_THROWS_AS(Coord(40, 10), out_of_range);
}

TEST_CASE("colonne hors borne") {
    CHECK_THROWS_AS(Coord(10, -2), out_of_range);
    CHECK_THROWS_AS(Coord(10, 100), out_of_range);
}
//question 4
TEST_CASE("une coordonnée") {
    Coord c(5, 10);
}
//question 6
TEST_CASE("getters coord") {
    Coord c(3, 6);
    CHECK(c.getLigne() == 3);
    CHECK(c.getColonne() == 6);
}
TEST_CASE("ligne hors borne") {
    CHECK_THROWS_AS(Coord(-1, 10), out_of_range);
    CHECK_THROWS_AS(Coord(40, 10), out_of_range);
}

TEST_CASE("colonne hors borne") {
    CHECK_THROWS_AS(Coord(5, -1), out_of_range);
    CHECK_THROWS_AS(Coord(5, 40), out_of_range);
}
//question 7 ,operateur d'affichage
ostream& operator<<(ostream& os, const Coord& c) {
    os << "(" << c.getLigne() << ", " << c.getColonne() << ")";
    return os;
}
//test question7(en plus)
TEST_CASE("Affichage Coord") {
    Coord c(1, 2);
    ostringstream oss;
    oss << c;
    CHECK(oss.str() == "(1, 2)");
}

        // Julien Cassou
// Q10
bool operator==(const Coord& c, const Coord&d) {
    return c.getLigne() == d.getLigne() && c.getColonne() == d.getColonne();
}

bool operator!=(const Coord& c, const Coord&d) {
    return c == d;
}

TEST_CASE("operateur == et !=") {
    Coord c(1,2);
    Coord d(3,4);
    CHECK( c == Coord (1,2));
    CHECK(c != d);
    CHECK(Coord (0,0) == Coord (0,0));
}

// Q11
Coord::Coord(int entier) {
    colonne = entier % TAILLEGRILLE;
    entier -= colonne;
    ligne = entier / TAILLEGRILLE;
}

int toInt(const Coord& c) {
    return c.getLigne() * TAILLEGRILLE + c.getColonne();
}

// Q12

TEST_CASE("toInt & constructeur à partir d'un entier") {
    CHECK(toInt(Coord(5,4)) == 204);
    CHECK(toInt(Coord (0,0)) == 0);
    Coord d {204};
    CHECK(d.getColonne() == 4);
    CHECK(d.getLigne() == 5);
}       //faut peut être ajouté des tests j'ai pas du faire tous les cas.