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
        Animal ajouteAnimal();
    private:
        Population population;
        Grille grille;
};