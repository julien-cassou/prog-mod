#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Jeu.hpp"
#include <SFML/Graphics.hpp>
using namespace std;

Param param;

int main() {
    sf::RenderWindow fenetre(sf::VideoMode(600,250), "Parametres");
    creerParam(fenetre, param);
    cout << "Lancement du jeu" << endl;
    Jeu jouer(param.ProbSpawnLapins, param.ProbSpawnRenards);
    sf::RenderWindow window(sf::VideoMode(Lwindow, Hwindow), "Simulation");
    jouer.simulation(param.NbTours, window, param);
    cout << "fin du Jeu";
    return 0;
}

