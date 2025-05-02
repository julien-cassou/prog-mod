#include <iostream>
#include "doctest.h"
#include "Jeu.hpp"
#include <stdexcept>
#include <sstream>
#include <vector>
#include <array>
#include <locale>
#include <fstream>
using namespace std;

        // Grille

// implémenté par Julien Cassou
Grille::Grille() {
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            grille[i][j] = 0;
        }
    }
}

// implémenté par Julien Cassou
bool Grille::CaseVide(Coord coordonnées) const {
    return (grille[coordonnées.getLigne()][coordonnées.getColonne()] == 0);
}

// implémenté par Julien Cassou
int Grille::getCase(Coord coordonnées) const{
    return grille[coordonnées.getLigne()][coordonnées.getColonne()];
}

// implémenté par Julien Cassou
void Grille::VideCase(Coord coordonnées) {
    grille[coordonnées.getLigne()][coordonnées.getColonne()] = 0;
}

// implémenté par Julien Cassou
void Grille::setCase(Coord coordonnées, int id) {
    if (!CaseVide(coordonnées)) VideCase(coordonnées);
    grille[coordonnées.getLigne()][coordonnées.getColonne()] = id;
}


        // Jeu

// implémenté par Julien Cassou
void Jeu::ajouteAnimal(Espece espece, Coord c) {
    if (!grille.CaseVide(c)) {
        throw runtime_error("Case occupée");
    }
    Animal temp(0, espece, c, FoodInit, AgeInit);
    population.set(temp);
    int id = temp.getId();
    // cout << "Création " << (espece == Espece::Lapin ? "lapin" : "renard") 
    //      << " à la position " << c << " avec ID: " << id << endl;
    grille.setCase(c, id);
}

// implémenté par Julien Cassou
Jeu::Jeu(double probLapins, double probRenard): population{}, grille{} {
    if(probLapins < 0 || probRenard < 0 || (probLapins + probRenard) > 1) {
		throw invalid_argument("Probabilités invalides");
	}

    for (int i = 0; i < TAILLEGRILLE; ++i) {
        for (int j = 0; j < TAILLEGRILLE; ++j) {
            double proba = static_cast<double>(rand()) / RAND_MAX;
            Coord c(i, j);
            if (proba < probLapins) {
                ajouteAnimal(Espece::Lapin, c);
            } else if (proba < probLapins + probRenard) {
                ajouteAnimal(Espece::Renard, c);
            }
        }
    }
}

// implémenté par Julien Cassou
void Jeu::verifieGrille() const {
    Ensemble identifiants = population.getIds();
    while(!identifiants.estVide()) {
        int id = identifiants.tire();
        Animal animal = population.get(id);
        Coord c = animal.getCoord();
        if (grille.getCase(c) != id) {
            throw runtime_error("Animal " + to_string(id) + 
                             ": (" + to_string(c.getLigne()) + "," + to_string(c.getColonne()) + 
                            ") mais sur Grille: " + to_string(grille.getCase(c)));
        }
    }
}

// implémenté par Julien Cassou
Ensemble Jeu::voisinsVides(Coord c) const {
    Ensemble res;
    Ensemble voisins = c.voisines();
    while(!voisins.estVide()) {
        Coord temp(voisins.tire());
        if (grille.CaseVide(temp)) res.ajoute(temp.toInt());
    }
    return res;
}

// implémenté par Julien Cassou
Ensemble Jeu::voisinsEspece(Coord c, Espece espece) const{
    Ensemble res;
    Ensemble voisins = c.voisines();
    while(!voisins.estVide()) {
        Coord temp = voisins.tire();
        int id = grille.getCase(temp);
        if (id != 0) {
            if(population.get(id).getEspece() == espece) {
                res.ajoute(temp.toInt());
            }
        }
    }
    return res;
}

// implémenté par Julien Cassou
void Jeu::Coherence() const {
    // Vérification grille -> population
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            Coord c(i, j);
            if (!grille.CaseVide(c)) {
                int id = grille.getCase(c);
                if (!population.estPresent(id)) {
                    throw runtime_error("Incohérence : l'animal " + to_string(id) + " est dans la grille mais pas dans la population");
                }
            }
        }
    }

    // Vérification population -> grille
    Ensemble ids = population.getIds();
    while (!ids.estVide()) {
        int id = ids.tire();
        Animal animal = population.get(id);
        Coord c = animal.getCoord();
        if (grille.getCase(c) != id) {
            throw runtime_error("Incohérence : l'animal " + to_string(id) + " est dans la population mais pas à la bonne position dans la grille");
        }
    }
}

// implémenté par Julien Cassou
void Jeu::DeplaceAnimal(int id) {
    try {
        // Vérifier que l'animal existe dans la population
        if (!population.estPresent(id)) {
            throw runtime_error("L'animal " + to_string(id) + " n'existe pas dans la population");
        }

        Animal animal = population.get(id);
        Coord c = animal.getCoord();
        
        animal.vieilli();
        population.supprime(id);
        population.set(animal);
        animal = population.get(id);
        // cout << animal.getAge()<< " " << animal.getFood() << endl;
        if(animal.estMort()) {
            // std::cout << "L'animal " + to_string(id) + " de type " + (animal.getEspece() == Espece::Lapin ? "Lapin" : "Renard") + " est mort de vieillesse à " + to_string(animal.getAge()) + " ans" << std::endl;
            grille.VideCase(c);
            population.supprime(id);
            return;
        }
        
        // Si c'est un renard et qu'il y a un lapin à la destination
        if (animal.getEspece() == Espece::Renard) {
            animal.jeune();
            Ensemble voisinsDisponibles = voisinsEspece(c, Espece::Lapin);
            if (voisinsDisponibles.estVide()) {
                if (animal.estMort()) {
                    grille.VideCase(c);
                    population.supprime(id);
                    // std::cout << "il est mort de faim" << endl;
                    return;
                }
                population.supprime(id);
                population.set(animal);
            }
            else {
                Coord newCoord(voisinsDisponibles.tire());
                int idProie = grille.getCase(newCoord);
                if (animal.estMort()) {
                    grille.VideCase(c);
                    population.supprime(id);
                    // std::cout << "il est mort de faim" << endl;
                    return;
                }
                try {
                    Animal proie = population.get(idProie);
                    if (proie.getEspece() == Espece::Lapin) {
                        // Le renard mange le lapin
                        grille.VideCase(c);
                        grille.VideCase(newCoord);
                        grille.setCase(newCoord, id);
                        animal.setCoord(newCoord);
                        animal.mange();
                        population.supprime(idProie);
                        // Mise à jour de l'animal dans la population
                        population.supprime(id);
                        population.set(animal);
                        return;
                    }
                } catch (const runtime_error& e) {
                throw runtime_error("Erreur lors de la tentative de manger un lapin : " + string(e.what()));
                }
            }
        }
        animal = population.get(id);
        Ensemble voisinsDisponibles = voisinsVides(c);
        if (voisinsDisponibles.estVide()) return;
        Coord newCoord(voisinsDisponibles.tire());
        // cout << animal.getAge();
        // Si la case de destination est vide
        if (grille.CaseVide(newCoord)) {
            grille.VideCase(c);
            grille.setCase(newCoord, id);
            animal.setCoord(newCoord);
            // Mise à jour de l'animal dans la population
            population.supprime(id);
            population.set(animal);
            return;
        }
    
        // Si on arrive ici, le déplacement n'est pas possible
        throw runtime_error("Déplacement impossible : case occupée");
    } catch (const runtime_error& e) {
        std::cout << "ERREUR - Animal " << id << ": " << e.what() << endl;
    }
}

// implémenté par Julien Cassou
void Jeu::affichage() const{
    for (int i = 0; i < TAILLEGRILLE; i++){
        for (int j = 0; j < TAILLEGRILLE; j++){
            Coord c(i, j);
            if (grille.CaseVide(c)){
                cout << ".";
            }else{
                int id = grille.getCase(c);
                Espece e = population.get(id).getEspece();
                if (e == Espece::Lapin) cout << "L";
                else if (e == Espece::Renard) cout << "R";
                }
            }
    cout << endl;
    }
}   

// implémenté par Julien Cassou
void Jeu::simulation(int Tours) {
    cout << "\n=== ÉTAT INITIAL ===" << endl;
    cout << "Nombre total d'animaux: " << population.getIds().cardinal() << endl;
    
    // Affichage initial des animaux
    Ensemble Ids = population.getIds();
    // while(!Ids.estVide()) {
    //     int temp = Ids.tire();
    //     Animal actuel = population.get(temp);
    //     if (actuel.getEspece() == Espece::Lapin) {
    //         cout << "Lapin " << temp << " - Position: " << actuel.getCoord() << endl;
    //     } else {
    //         cout << "Renard " << temp << " - Position: " << actuel.getCoord() << " - Nourriture: " << actuel.getFood() << endl;
    //     }
    // }
    
    cout << "\nGrille initiale:" << endl;
    affichage();
    
    // Génération de l'image initiale
    string nomFichier = "img000.ppm";
    genereImagePPM(nomFichier);
    
    for (int i = 1; i <= Tours; i++) {
        cout << "\n=== TOUR " << i << " ===" << endl;
        
        // Affichage de l'état initial du tour
        cout << "\nÉtat initial de la population:" << endl;
        cout << "Nombre total d'animaux: " << population.getIds().cardinal() << endl;
        
        // randomisation des déplacements
        Ids = population.getIds();
        Ensemble lapin;
        Ensemble renard;
        
        while(!Ids.estVide()) {
            int temp = Ids.tire();
            Animal actuel = population.get(temp);
            if (actuel.getEspece() == Espece::Lapin) {
                lapin.ajoute(temp);
                // cout << "Lapin " << temp << " - Position: " << actuel.getCoord() << endl;
            } else {
                renard.ajoute(temp);
                // cout << "Renard " << temp << " - Position: " << actuel.getCoord() << " - Nourriture: " << actuel.getFood() << endl;
            }
        }
        
        cout << "Nombre de lapins: " << lapin.cardinal() << endl;
        cout << "Nombre de renards: " << renard.cardinal() << endl;

        // randomisation déplacements
        Ids = population.getIds();
        while(!Ids.estVide()) {
            int temp = Ids.tire();
            // cout << temp << " ";
            if (!population.estPresent(temp)) {
                // cout << "L'animal est mort" << endl;
            }
            else {
                Animal actu = population.get(temp);
                Coord c = actu.getCoord();
                Ensemble vide = voisinsVides(c);
                Espece e = actu.getEspece();
                // if (i >= 75) cout << actu.getFood();
                try {
                    DeplaceAnimal(temp);
                    if (actu.seReproduit(vide.cardinal())) {
                        // if (e == Espece::Renard) cout << actu.getFood();
                        Animal nouveau(0, e, c, FoodInit, 0);
                        population.set(nouveau);
                        int id = nouveau.getId();
                        grille.setCase(c, id);
                    }
                } catch (const runtime_error& e) {
                    cout << "ERREUR - " << temp << ": " << e.what() << endl;
                }
                // Vérification de la cohérence
                try {
                    Coherence();
                } catch (const runtime_error& e) {
                    cout << "ERREUR DE COHÉRENCE: " << e.what() << endl;
                }
            }
        }
         // Affichage de la grille après le tour
        cout << "\nÉtat final de la grille après le tour " << i << ":" << endl;
        affichage();
    
        // Génération de l'image pour ce tour
        char nomFichier[20];
        sprintf(nomFichier, "img%03d.ppm", i);
        genereImagePPM(nomFichier);
    }
}

// implémenté par Julien Cassou
void Jeu::genereImagePPM(const string& nomFichier) const {
    ofstream fichier(nomFichier);
    if (!fichier) {
        throw runtime_error("Impossible d'ouvrir le fichier " + nomFichier);
    }

    // En-tête PPM
    fichier << "P3" << endl;
    fichier << TAILLEGRILLE << " " << TAILLEGRILLE << endl;
    fichier << "255" << endl;

    // Données de l'image
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            Coord c(i, j);
            if (grille.CaseVide(c)) {
                // Case vide en blanc
                fichier << "255 255 255 ";
            } else {
                int id = grille.getCase(c);
                Espece e = population.get(id).getEspece();
                if (e == Espece::Lapin) {
                    // Lapin en bleu
                    fichier << "0 0 255 ";
                } else {
                    // Renard en rouge
                    fichier << "255 0 0 ";
                }
            }
        }
        fichier << endl;
    }
}

Population Jeu::getPopulation() const {
    return population;
}