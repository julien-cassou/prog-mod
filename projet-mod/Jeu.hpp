#ifndef JEU_HPP
#define JEU_HPP
#include <stdexcept>
#include <ostream>
#include <vector>
#include <array>
#include "coord.hpp"
#include "Animal.hpp"
using namespace std;


class Grille {
    public:
        // Constructeur;
        Grille();
        // Méthodes
        bool CaseVide(Coord coordonnées) const;
        int getCase(Coord coordonnées) const;
        void VideCase(Coord coordonnées);
        void setCase(Coord coordonnées, int id);
    private:
        array<array<int, TAILLEGRILLE>, TAILLEGRILLE> grille;
};

class Jeu {
    public:
        // Constructeur
        Jeu(double probLapins, double probRenard);
        // méthodes
        void ajouteAnimal(Espece espece, Coord c);
        void verifieGrille() const;
        Ensemble voisinsVides(Coord Case) const;
        Ensemble voisinsEspece(Coord Case, Espece espece) const;
        void DeplaceAnimal(Animal &animal);
        void Coherence() const;
    private:
        Population population;
        Grille grille;
};

#endif