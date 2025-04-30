//
//  main.cpp
//  coordonées
//
//  Created by Lucia Casalta on 02/04/2025.
//
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
<<<<<<< Updated upstream
#include "coord.hpp"
=======
#include "Jeu.hpp"
>>>>>>> Stashed changes
using namespace std;

//question 8
int main() {
    Jeu jouer(0.20, 0.07);
    // Jeu jouer(0.1, 0.1);
    jouer.simulation(5);
    cout << "fin du Jeu";

    //MASSIce

    // Jeu jeu(0.2, 0.07);

    // jeu.afficherGrille();


    // for (int i = 1; i <= 100; i++ ) {
    //     cout << "Tour " << i << endl;

    //     Population pop = jeu.getPopulation();
    //     Ensemble Ids = pop.getIds();
    //     vector<int> lapin;
    //     vector<int> renard;
    //     while(!Ids.estVide()) {
    //         int temp = Ids.tire();
    //         Animal actuel = pop.get(temp);
    //         if (actuel.getEspece() == Espece::Lapin) lapin.push_back(temp);
    //         else renard.push_back(temp);
    //     }

    //     // Déplacement des lapins
    //     for (int id : lapin) {
    //         if (pop.get(id).getEspece() == Espece::Lapin) {
    //             jeu.DeplaceAnimal(id);
    //         }
    //     }
    //     // Déplacement des renards
    //     for (int id : renard) {
    //         if (pop.get(id).getEspece() == Espece::Renard) {
    //             jeu.DeplaceAnimal(id);
    //         }
    //     }

    //     // Affichage après le tour
    //     jeu.afficherGrille();
    // }

    // cout << "\nSimulation terminée." << endl;

<<<<<<< Updated upstream
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
=======
>>>>>>> Stashed changes
    return 0;
}
