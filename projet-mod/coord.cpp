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

//constructeur
//crée une coordonnée valide,lance une exception si hors de la grille
Coord::Coord(int l, int c) {
    if (l < 0 || l >= TAILLEGRILLE || c < 0 || c >= TAILLEGRILLE) {
        throw std::out_of_range("en dehors de la grille");
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
    CHECK_THROWS_AS(Coord(-1, 10), std::out_of_range);
    CHECK_THROWS_AS(Coord(40, 10), std::out_of_range);
}

TEST_CASE("colonne hors borne") {
    CHECK_THROWS_AS(Coord(10, -2), std::out_of_range);
    CHECK_THROWS_AS(Coord(10, 100), std::out_of_range);
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
    CHECK_THROWS_AS(Coord(-1, 10), std::out_of_range);
    CHECK_THROWS_AS(Coord(40, 10), std::out_of_range);
}

TEST_CASE("colonne hors borne") {
    CHECK_THROWS_AS(Coord(5, -1), std::out_of_range);
    CHECK_THROWS_AS(Coord(5, 40), std::out_of_range);
}
//question 7 ,operateur d'affichage
std::ostream& operator<<(std::ostream& os, const Coord& c) {
    os << "(" << c.getLigne() << ", " << c.getColonne() << ")";
    return os;
}
//test question7(en plus)
TEST_CASE("Affichage Coord") {
    Coord c(1, 2);
    std::ostringstream oss;
    oss << c;
    CHECK(oss.str() == "(1, 2)");
}
