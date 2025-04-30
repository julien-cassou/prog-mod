#include <iostream>
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


//question 7 ,operateur d'affichage
ostream &operator<<(ostream& os, const Coord& c) {
    os << "(" << c.getLigne() << "," << c.getColonne() << ")";
    return os;
}

<<<<<<< Updated upstream
        // Julien Cassou
// Q10
bool operator==(const Coord& c, const Coord&d) {
=======
bool operator==(const Coord &c, const Coord &d) {
>>>>>>> Stashed changes
    return c.getLigne() == d.getLigne() && c.getColonne() == d.getColonne();
}

bool operator!=(const Coord& c, const Coord&d) {
    return !(c == d);
}

Coord::Coord(int entier) {
    colonne = entier % TAILLEGRILLE;
    entier -= colonne;
    ligne = entier / TAILLEGRILLE;
}

int toInt(const Coord& c) {
    return c.getLigne() * TAILLEGRILLE + c.getColonne();
}

<<<<<<< Updated upstream
// Q12

TEST_CASE("toInt & constructeur à partir d'un entier") {
    CHECK(toInt(Coord(5,4)) == 204);
    CHECK(toInt(Coord (0,0)) == 0);
    Coord d {204};
    CHECK(d.getColonne() == 4);
    CHECK(d.getLigne() == 5);
}       //faut peut être ajouté des tests j'ai pas du faire tous les cas.

// Ex 3
// Q2

=======
>>>>>>> Stashed changes
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


Ensemble::Ensemble() {
    card = 0;
    for (int i = 0; i < MAXCARD; i++) {
        t[i] = 0;
    }
}


int Ensemble::cardinal() const{
    return card;
}

bool Ensemble::estVide() const {
    return (cardinal() == 0);
}


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

int Ensemble::tire() {
    if (cardinal() == 0) {
        throw runtime_error("L'ensemble est vide");
    }
    int indice = rand() % (cardinal());
    int elem = t[indice];
    for (int i = indice; i < cardinal() - 1; i++) {
        t[i] = t[i+1];
    }
    t[cardinal() - 1] = 0;
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
                res.ajoute(toInt(temp));
            }
        }
    }
    return res;
<<<<<<< Updated upstream
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
=======
>>>>>>> Stashed changes
}