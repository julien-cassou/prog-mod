#ifndef JEU_HPP
#define JEU_HPP
#include <iostream>
#include <stdexcept>
#include <vector>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>
#include "Animal.hpp"
using namespace std;

const int Lwindow = 800;
const int Hwindow = 650;

const float taille = 600.f / 40.0;

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
        void simulation(int nbTours, sf::RenderWindow& window, const Param &p);
        void effectuerUnTour(const Param &p);
        void afficherEtat(sf::RenderWindow& window, int nbtours) const;
        // accesseur --> test
        Population getPopulation() const;
    private:
        Population population;
        Grille grille;
};

void creerParam(sf::RenderWindow& window, Param &p);
#endif