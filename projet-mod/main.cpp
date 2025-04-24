//
//  main.cpp
//  coordonées
//
//  Created by Lucia Casalta on 02/04/2025.
//
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "coord.hpp"
#include "Animal.hpp"
#include "Jeu.cpp"
using namespace std;

//question 8
int main() {
    try {
        //création d'une coordonnée valide
        Coord c(8, 15);

        //affichage
        cout << "Voici ma coordonnée : " << c << endl;
    }
    catch (const out_of_range& e) {
        cerr << "Erreur : " << e.what() << endl;
    }
    Ensemble e;
    e.ajoute(5);    
    e.ajoute(3);  
    e.ajoute(1); 
    if (e.estVide()) {
        cout << "vide";
    }else{ cout << e;}
    
    Animal Renard = {3, Espece::Renard, Coord (6,13)};
    Renard.mange();
    for (int i = 0; i < 5; i++){
        cout << "Le Renard se reproduit: " << Renard.seReproduit(0);
    }
    Animal Lapin = {3, Espece::Lapin, Coord (7,13)};
    for (int j = 0; j < 5; j++){
        cout << "Le Lapin se reproduit: " << Lapin.seReproduit(5);
    }
    return 0;
}
