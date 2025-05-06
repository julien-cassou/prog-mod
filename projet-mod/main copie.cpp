#include <iostream>
#include <filesystem>
#include "coord.hpp"
#include "statistiques.hpp"
#include "Jeu.hpp"

using namespace std;

int main() {
    srand(time(0)); //initialise
    
    filesystem::create_directory("images");
    
    //cree fichier resultat.csv
    Jeu jeu(0.2, 0.05); // 20% lapins, 5% renards
    Statistiques stats("resultats.csv");
    
    //boucle sur 20 tours(modif si on veut rajouter des tours)
    for (int tour = 0; tour < 20; ++tour) {
        cout << "Tour " << tour + 1 << endl;

        jeu.affichage();
        string nom = "images/image_" + to_string(tour + 1) + ".ppm";//genere image ppm
        jeu.genereImagePPM(nom); // sauvegarde

        jeu.simulation(1); //+1 tour simulation
        
        //recup nombre de lapins et renards apres le tour
        int nbLapins = jeu.getPopulation().nbLapins();
        int nbRenards = jeu.getPopulation().nbRenards();
        stats.enregistrer(tour, nbLapins, nbRenards);

        cout << "Lapins : " << nbLapins << ", Renards : " << nbRenards << endl;
    }

    return 0;
}

