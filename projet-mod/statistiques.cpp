#include "statistiques.hpp"
#include <fstream>
#include <string>

//constructeur
Statistiques::Statistiques(const std::string& nomFichier) {
    fichier.open(nomFichier);
    fichier << "Tour,Lapins,Renards\n";
}

//méthode pour enregistrer une ligne de statistiques
void Statistiques::enregistrer(int tour, int nbLapins, int nbRenards) {
    fichier << tour << "," << nbLapins << "," << nbRenards << "\n";
}
