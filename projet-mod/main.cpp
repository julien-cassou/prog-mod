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
    return 0;
}
