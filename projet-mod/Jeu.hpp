#include <stdexcept>
#include <ostream>
#include <vector>
#include <array>
#include <string>
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
        Ensemble voisinsVides(Coord c) const;
        Ensemble voisinsEspece(Coord c, Espece espece) const;
        void DeplaceAnimal(int id);
        void Coherence() const;
        void simulation(int Tours);
        void affichage() const;
        void genereImagePPM(const string& nomFichier) const;
        // accesseur --> test
        Population getPopulation() const;
    private:
        Population population;
        Grille grille;
};