#include <iostream>
#include <filesystem> // pour dossier image
#include "coord.hpp"
using namespace std;

int main() {
    srand(time(0)); // comportement aléatoire

    std::filesystem::create_directory("images"); // crée le dossier

    Jeu jeu(0.2, 0.05); // 20 % lapins, 5 % renards

    for (int tour = 0; tour < 20; ++tour) {
        cout << "Tour " << tour + 1 << endl;

        jeu.afficheTexte();   // affichage
        
        //sauvegarde image ppm dans le dossier images
        string nom = "images/image_" + to_string(tour + 1) + ".ppm";
        jeu.exportPPM(nom);

        jeu.etape();          // axécution du tour

        //stat
        cout << "Lapins : " << jeu.getPopulation().nbLapins()
             << ", Renards : " << jeu.getPopulation().nbRenards() << endl;
    }

    return 0;
}
