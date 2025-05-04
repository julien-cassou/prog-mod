#include <iostream>
#include "doctest.h"
#include "Jeu.hpp"
#include <stdexcept>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>
#include <SFML/Graphics.hpp>
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

void creerParam(sf::RenderWindow& window, Param &p) {
    int parametreActif = 0;
    std::vector<std::string> noms = {"Probabilité reproduction lapin", "Probabilité reproduction renard", "Proabilité Lapins", "Probabilité Renard", "Nb Tours"};
    std::vector<float*> valeurs = {
        &p.ProBirthLapin, 
        &p.ProBirthRenard, 
        &p.ProbSpawnLapins, 
        &p.ProbSpawnRenards, 
        reinterpret_cast<float*>(&p.NbTours),
    };

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.key.code == sf::Keyboard::Enter) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Down) {
                parametreActif = (parametreActif + 1) % noms.size();
            }
            if (event.key.code == sf::Keyboard::Up) {
                parametreActif = (parametreActif - 1 + noms.size()) % noms.size();
            }
            if (event.key.code == sf::Keyboard::Right) {
                if (parametreActif == 4) {
                    *valeurs[parametreActif] = min(200, (int)(*valeurs[parametreActif] + 5));
                }
                *valeurs[parametreActif] += 0.1f;
            }
            if (event.key.code == sf::Keyboard::Left) {
                if (parametreActif == 4) {
                    *valeurs[parametreActif] = max(1, (int)(*valeurs[parametreActif] - 1));
                }
                *valeurs[parametreActif] = max(0.01f, *valeurs[parametreActif] - 0.01f);
            }
        }
    }

    window.clear();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("La police ne se charge pas");
    }
    
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    
    for (size_t i = 0; i < noms.size(); ++i) {
        text.setString(noms[i] + ": " + std::to_string(*valeurs[i]));
        text.setPosition(10, 30 + i * 30);
        window.draw(text);
    }

    window.display();
}


// implémenté par Julien Cassou
void Jeu::simulation(int nbTours, sf::RenderWindow& window, const Param &p) {
    sf::Clock clock;
    int nbtours = 1;
    bool enPause = false;
    vector<float> timespeed = {0.25f ,0.75f ,1.5f ,2.0f, 2.5f, 3.0f, 5.0f};
    int indice = 3;

    while (window.isOpen() && nbtours <= nbTours) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    enPause = !enPause;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    indice = max(0, indice - 1);
                }
                if (event.key.code == sf::Keyboard::Left) {
                    indice = min(6, indice + 1);
                }
            }
        }
        if (!enPause and clock.getElapsedTime().asSeconds() >= timespeed[indice]) {
            effectuerUnTour(p);
            nbtours++;
            clock.restart();
        }

        window.clear();
        afficherEtat(window, nbtours);
        window.display();
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        throw runtime_error("la police ne se charge pas");
    }
    sf::Text fin;
    fin.setFont(font);
    fin.setCharacterSize(32);
    fin.setFillColor(sf::Color::Green);
    fin.setString("Simulation terminee");
    fin.setPosition(250, Hwindow / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        window.clear();
        window.draw(fin);
        window.display();
    }
}

void Jeu::effectuerUnTour(const Param &p) {
    Ensemble Ids = population.getIds();
    while (!Ids.estVide()) {
        int temp = Ids.tire();
        if (!population.estPresent(temp)) continue;

        Animal actu = population.get(temp);
        Coord c = actu.getCoord();
        Ensemble vide = voisinsVides(c);
        Espece e = actu.getEspece();

        try {
            DeplaceAnimal(temp);
            if (actu.seReproduit(vide.cardinal(), p)) {
                Animal nouveau(0, e, c, FoodInit, 0);
                population.set(nouveau);
                grille.setCase(c, nouveau.getId());
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "ERREUR - " << temp << ": " << e.what() << std::endl;
        }

        try {
            Coherence();
        } catch (const std::runtime_error& e) {
            std::cerr << "ERREUR DE COHÉRENCE: " << e.what() << std::endl;
        }
    }
}


void Jeu::afficherEtat(sf::RenderWindow& window, int nbtours) const {
    Ensemble Ids = population.getIds();
    Ensemble lapin, renard;
    int tot = Ids.cardinal();
    while (!Ids.estVide()) {
        int temp = Ids.tire();
        Animal actuel = population.get(temp);
        if (actuel.getEspece() == Espece::Lapin)
            lapin.ajoute(temp);
        else
            renard.ajoute(temp);
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        throw runtime_error("la police ne se charge pas");
    }

    sf::Text tour;
    tour.setFont(font);
    tour.setCharacterSize(24);
    tour.setFillColor(sf::Color::White);
    tour.setPosition(10, 10);
    tour.setString("Tours : " + std::to_string(nbtours));

    sf::Text texte;
    texte.setFont(font);
    texte.setCharacterSize(20);
    texte.setFillColor(sf::Color::White);
    std::ostringstream oss;
    oss << "Total animaux: " << tot << "\n"
        << "Lapins: " << lapin.cardinal() << "\n"
        << "Renards: " << renard.cardinal();
    texte.setString(oss.str());
    texte.setPosition(620, 50);

    window.draw(tour);
    window.draw(texte);

    for (int i = 0; i < TAILLEGRILLE; ++i) {
        for (int j = 0; j < TAILLEGRILLE; ++j) {
            sf::RectangleShape cellule(sf::Vector2f(taille, taille));
            float posY = Hwindow - (i + 1) * taille; // permet de faire partir la grille d'en bas à droite
            cellule.setPosition(j * taille, posY);
            cellule.setOutlineThickness(1);
            cellule.setOutlineColor(sf::Color::Black);

            Coord c(i, j);
            if (grille.CaseVide(c)) {
                cellule.setFillColor(sf::Color::White);
            } else {
                int id = grille.getCase(c);
                Espece e = population.get(id).getEspece();
                if (e == Espece::Lapin) {
                        cellule.setFillColor(sf::Color::Blue);
                    }
                else {
                    cellule.setFillColor(sf::Color::Red);
                }
            }
            window.draw(cellule);
        }
    }
}