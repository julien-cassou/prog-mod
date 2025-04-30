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
        Grille() : grille{} {};
        // Méthodes
        bool CaseVide(Coord coordonnées) const;
        int getCase(Coord coordonnées, Population pop) const;
        void VideCase(Coord coordonnées);
        void setCase(Coord coordonnées, int id);
    private:
        vector<vector<Coord>> grille;
};

class Jeu {
    public:
<<<<<<< Updated upstream
        Animal ajouteAnimal();
=======
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

        //massi

        // void afficherGrille() const;
        // Population getPopulation() const;
>>>>>>> Stashed changes
    private:
        Population population;
        Grille grille;
};