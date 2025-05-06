#include <iostream>
#include "coord.hpp"
#include "doctest.h"
#include <stdexcept>
#include <sstream>
#include <vector>
using namespace std;

    // Coord

// implémenté par Lucia Casalta
Coord::Coord(int l, int c) {
    if (l < 0 || l >= TAILLEGRILLE || c < 0 || c >= TAILLEGRILLE) {
        throw out_of_range("en dehors de la grille");
    }
    ligne = l;
    colonne = c;
}

// implémenté par Lucia Casalta
int Coord::getLigne() const {
    return ligne;
}

// implémenté par Lucia Casalta
int Coord::getColonne() const {
    return colonne;
}


// implémenté par Lucia Casalta
ostream &operator<<(ostream& os, const Coord& c) {
    os << "(" << c.getLigne() << "," << c.getColonne() << ")";
    return os;
}

// implémenté par Julien Cassou
bool operator==(const Coord &c, const Coord &d) {
    return c.getLigne() == d.getLigne() && c.getColonne() == d.getColonne();
}

// implémenté par Julien Cassou
bool operator!=(const Coord& c, const Coord&d) {
    return !(c == d);
}

// implémenté par Julien Cassou
Coord::Coord(int entier) {
    colonne = entier % TAILLEGRILLE;
    entier -= colonne;
    ligne = entier / TAILLEGRILLE;
}

// implémenté par Julien Cassou
int Coord::toInt() {
    return getLigne() * TAILLEGRILLE + getColonne();
}

// implémenté par Julien Cassou
void Ensemble::affiche(ostream& out) const {
    for (int i = 0; i < card; i++) {
        int c = t[i] % TAILLEGRILLE;
        int l = (t[i] - c) / TAILLEGRILLE;
        out << Coord(l,c) << " ";
    }
}

// implémenté par Julien Cassou
ostream &operator<<(ostream& out, const Ensemble& e) {
    e.affiche(out);
    return out;
}

// implémenté par Julien Cassou
Ensemble::Ensemble() {
    card = 0;
    for (int i = 0; i < MAXCARD; i++) {
        t[i] = 0;
    }
}

// implémenté par Julien Cassou
int Ensemble::cardinal() const{
    return card;
}

// implémenté par Julien Cassou
bool Ensemble::estVide() const {
    return (cardinal() == 0);
}

// implémenté par Julien Cassou
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

// implémenté par Julien Cassou
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

/** méthode pour créer des ensembles de tests 
 */
// implémenté par Julien Cassou
void Ensemble::nouvelle_ensemble(int taille) {
    Ensemble e;
    for (int i = 0; i < taille; i++) {
        t[i] = rand() % 20;
        card++;
    }
}

// implémenté par Julien Cassou
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