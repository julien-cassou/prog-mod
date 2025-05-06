#ifndef STATISTIQUES_HPP
#define STATISTIQUES_HPP

#include <fstream>
#include <string>

class Statistiques {
public:
    Statistiques(const std::string& nomFichier);
    void enregistrer(int tour, int nbLapins, int nbRenards);

private:
    std::ofstream fichier;
};

#endif
