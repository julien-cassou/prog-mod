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
#include <vector>
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
    CHECK_THROWS_AS(Coord(TAILLEGRILLE, TAILLEGRILLE), out_of_range);
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
ostream &operator<<(ostream& os, const Coord& c) {
    os << "(" << c.getLigne() << "," << c.getColonne() << ")";
    return os;
}
//test question7(en plus)
TEST_CASE("Affichage Coord") {
    Coord c(1, 2);
    ostringstream oss;
    oss << c;
    CHECK(oss.str() == "(1,2)");
}

        // Julien Cassou
// Q10
bool operator==(const Coord &c, const Coord &d) {
    return c.getLigne() == d.getLigne() && c.getColonne() == d.getColonne();
}

bool operator!=(const Coord &c, const Coord&d) {
    return !(c == d);
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

int Coord::toInt() const {
    return getLigne() * TAILLEGRILLE + getColonne();
}

// Q12

TEST_CASE("toInt & constructeur à partir d'un entier") {
    CHECK(Coord(5,4).toInt() == 204);
    CHECK(Coord (0,0).toInt() == 0);
    Coord d {204};
    CHECK(d.getColonne() == 4);
    CHECK(d.getLigne() == 5);
}       //faut peut être ajouté des tests j'ai pas du faire tous les cas.

// Ex 3
// Q2

void Ensemble::affiche(ostream& out) const {
    for (int i = 0; i < card; i++) {
        int c = t[i] % TAILLEGRILLE;
        int l = (t[i] - c) / TAILLEGRILLE;
        out << Coord(l,c) << " ";
    }
}

ostream &operator<<(ostream& out, const Ensemble& e) {
    e.affiche(out);
    return out;
}

// Q3
Ensemble::Ensemble() {
    card = 0;
    for (int i = 0; i < MAXCARD; i++) {
        t[i] = 0;
    }
}

// Q4

int Ensemble::cardinal() const{
    return card;
}

bool Ensemble::estVide() const {
    return (cardinal() == 0);
}

// Q5

void Ensemble::ajoute(int entier) {
    int c = cardinal();
    if (c >= MAXCARD) {
        throw runtime_error("L'ensemble est plein");
    }
    if(c == 0) {t[0] = entier;}
    else {
        t[c] = entier;
    }
    card++;
}

/** tire
 * @return l'indice d'un des membres de l'ensemble de manière aléatoire
 **/
int Ensemble::tire() {
    if (cardinal() == 0) {
        throw runtime_error("L'ensemble est vide");
    }
    int indice = rand() % (cardinal() + 1);
    int elem = t[indice];
    for (int i = indice; i < cardinal() - 1; i++) {
        t[i] = t[i+1];
    }
    t[cardinal()] = 0;
    card--;
    return elem;
}

/** méthode pour créer des ensembles de tests **/
    // Julien
void Ensemble::nouvelle_ensemble(int taille) {
    Ensemble e;
    for (int i = 0; i < taille; i++) {
        t[i] = rand() % 20;
        card++;
    }
}

TEST_CASE("cardinal") {
    Ensemble t;
    t.nouvelle_ensemble(5);
    CHECK(t.cardinal() == 5);
    t.ajoute(9);
    CHECK(t.cardinal() == 6);
    Ensemble e;
    CHECK(e.cardinal() == 0);
}

TEST_CASE("estVide") {
    Ensemble t;
    t. nouvelle_ensemble(5);
    CHECK_FALSE(t.estVide());
    Ensemble e;
    CHECK(e.estVide());
}

TEST_CASE("ajoute") {
    Ensemble e;
    e.nouvelle_ensemble(MAXCARD);
    CHECK_THROWS_AS(e.ajoute(4), runtime_error);
    Ensemble t;
    t.ajoute(1);
    CHECK(t.cardinal() == 1);
}

TEST_CASE("tire" ) {
    Ensemble e;
    CHECK_THROWS_AS(e.tire(), runtime_error);
    Ensemble j;
    j.nouvelle_ensemble(5);
    j.tire();
    CHECK(j.cardinal() == 4);
    Ensemble p;
    p.nouvelle_ensemble(1);
    p.tire();
    CHECK(p.estVide());
}

// Ex 4
    // Q1

Ensemble Coord::voisines() const {
    Ensemble res;
    int i_max = min(ligne + 1, TAILLEGRILLE -1);  //49 
    int i_min = max(ligne -1, 0);  //49
    int j_max = min(colonne + 1, TAILLEGRILLE-1);
    int j_min = max(colonne - 1, 0);
    for (int i = i_min; i <= i_max; i++) {
        for (int j = j_min; j <= j_max; j++) {
            Coord temp = Coord(i,j);
            if (temp != (Coord (ligne,colonne))) {
                res.ajoute(temp.toInt());
            }
        }
    }
    return res;
}

// Q2

TEST_CASE("voisines") {
    Coord c1 = Coord(0,0);
    Coord c2 = Coord(TAILLEGRILLE - 1,TAILLEGRILLE - 1);
    Coord c3 = Coord(0,TAILLEGRILLE - 1);
    Coord c4 = Coord(TAILLEGRILLE - 1,0);
    Coord c5 = Coord(3,4);
    Coord c6 = Coord(4,3);
    Ensemble e1 = c1.voisines();
    CHECK(e1.cardinal() == 3);
    ostringstream os;
    e1.affiche(os);
    CHECK(os.str() == "(0,1) (1,0) (1,1) ");
    Ensemble e2 = c2.voisines();
    CHECK(e2.cardinal() == 3);
    ostringstream oss;
    e2.affiche(oss);
    CHECK(oss.str() == "(38,38) (38,39) (39,38) ");
    Ensemble e3 = c3.voisines();
    CHECK(e3.cardinal() ==3);
    Ensemble e4 = c4.voisines();
    CHECK(e4.cardinal() == 3);
    Ensemble e5 = c5.voisines();
    CHECK(e5.cardinal() == 8);
    Ensemble e6 = c6.voisines();
    CHECK(e6.cardinal() == 8);
}
