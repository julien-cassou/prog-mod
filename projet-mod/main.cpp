//
//  main.cpp
//  coordonées
//
//  Created by Lucia Casalta on 02/04/2025.
//

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include "coord.hpp"
//question 8
int main() {
    try {
        //création d'une coordonnée valide
        Coord c(8, 15);

        //affichage
        std::cout << "Voici ma coordonnée : " << c << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
