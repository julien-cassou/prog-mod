#include "coord.hpp"
//#include "doctest.h"
#include <stdexcept>
#include <sstream>
#include <vector>
#include <unordered_map> //je sais pas pourquoi ca buguait alors j'ai du rajouter ca
#include <iostream>
#include <fstream>
using namespace std;

//constructeur
//crée une coordonnée valide,lance une exception si hors de la grille
Coord::Coord(int l, int c) {
    if (l < 0 || l >= TAILLEGRILLE || c < 0 || c >= TAILLEGRILLE) {
        throw out_of_range("en dehors de la grille");
    }
    ligne = l;
    colonne = c;
}

//accesseur ligne,question 5(getters)
int Coord::getLigne() const {
    return ligne;
}

//accesseur colonne
int Coord::getColonne() const {
    return colonne;
}


//question 7 ,operateur d'affichage
ostream &operator<<(ostream& os, const Coord& c) {
    os << "(" << c.getLigne() << "," << c.getColonne() << ")";
    return os;
}


        // Julien Cassou
// Q10
bool operator==(const Coord& c, const Coord&d) {
    return c.getLigne() == d.getLigne() && c.getColonne() == d.getColonne();
}

bool operator!=(const Coord& c, const Coord&d) {
    return !(c == d);
}



// Q11
Coord::Coord(int entier) {
    colonne = entier % TAILLEGRILLE;
    entier -= colonne;
    ligne = entier / TAILLEGRILLE;
}

int toInt(const Coord& c) {
    return c.getLigne() * TAILLEGRILLE + c.getColonne();
}



void Ensemble::affiche(ostream& out) const {
    for (int i = 0; i < card; i++) {
        int c = t[i] % TAILLEGRILLE;
        int l = (t[i] - c) / TAILLEGRILLE;
        out << Coord(l,c) << " ";
    }
}

ostream &operator<<(ostream& out, const Ensemble& e) {
    e.affiche(out);
    return out;
}

// Q3
Ensemble::Ensemble() {
    card = 0;
    for (int i = 0; i < MAXCARD; i++) {
        t[i] = 0;
    }
}

// Q4

int Ensemble::cardinal() const{
    return card;
}

bool Ensemble::estVide() const {
    return (cardinal() == 0);
}

// Q5

void Ensemble::ajoute(int entier) {
    int c = cardinal();
    if (c >= MAXCARD) {
        throw runtime_error("L'ensemble est plein");
    }
    if(c == 0) {t[0] = entier;}
    else {
        t[c] = entier;
    }
    card++;
}

int Ensemble::tire() {
    if (cardinal() == 0) {
        throw runtime_error("L'ensemble est vide");
    }
    int indice = rand() % (cardinal() + 1);
    int elem = t[indice];
    for (int i = indice; i < cardinal() - 1; i++) {
        t[i] = t[i+1];
    }
    t[cardinal()] = 0;
    card--;
    return elem;
}
int Ensemble::get(int i) const {
    if (i < 0 || i >= card) {
        throw std::out_of_range("Indice hors limites dans Ens");
    }
    return t[i];
}

/** méthode pour créer des ensembles de tests **/
    // Julien
void Ensemble::nouvelle_ensemble(int taille) {
    Ensemble e;
    for (int i = 0; i < taille; i++) {
        t[i] = rand() % 20;
        card++;
    }
}

// Ex 4
    // Q1

Ensemble Coord::voisines() const {
    Ensemble res;
    int i_max = min(ligne + 1, TAILLEGRILLE -1);  //49
    int i_min = max(ligne -1, 0);  //49
    int j_max = min(colonne + 1, TAILLEGRILLE-1);
    int j_min = max(colonne - 1, 0);
    for (int i = i_min; i <= i_max; i++) {
        for (int j = j_min; j <= j_max; j++) {
            Coord temp = Coord(i,j);
            if (temp != (Coord (ligne,colonne))) {
                res.ajoute(toInt(temp));
            }
        }
    }
    return res;
}



// Cours TD


ostream& operator<<(ostream& out, Espece espece) {
    switch(espece) {
        case Espece::Renard: out << "Renard"; break;
        case Espece::Lapin: out << "Lapin"; break;
        default: throw runtime_error("espèce non reconnué");
    }
    return out;
}



Animal::Animal(int id, Espece espece, Coord coord) : id{id} , espece{espece}, coord{coord}, food{FoodInit} {};

//constructeur par défaut
Animal::Animal() : id(-1), espece(Espece::Lapin), coord(0, 0), food(FoodInit) {}

int Animal::getId() const {
    return id;
}


Coord Animal::getCoord() const {
    return coord;
}

void Animal::setCoord(Coord c) {
    coord = c;
}

Espece Animal::getEspece() const {
    return espece;
}



ostream& Animal::affiche(ostream &out) const {
    out << "Animal: " << id << ", " << espece << ", " << coord;
    if (espece == Espece::Renard ) {
        out << ", " << food;
    }
    return out;
}

bool Animal::estMort() const {
    if (espece == Espece::Renard) {
        if (food == 0) {
            return true;
        }
    }
    return false;
}

void Animal::jeune() {
    if (espece == Espece::Lapin) {
        throw runtime_error("Un lapin mange tous le temps de l'herbe");
    }
    else {
        food -= 1;
    }
}



bool Animal::seReproduit(int nbVoisin) const {
    if (espece == Espece::Renard and food >= FoodReprod) {
        return (static_cast<double>(rand()) / RAND_MAX) < ProBirthRenard; // Vérifie si la reproduction réussit
    }
    else if (nbVoisin >= MinFreeBirthLapin) {
        return (static_cast<double>(rand()) / RAND_MAX) < ProBirthLapin; // Vérifie si la reproduction réussit
    }
    return false;
}

void Animal::mange() {
    if (espece == Espece::Lapin) {
        throw runtime_error("Un lapin ne mange que de l'herbe");
    }
    else {
        food += FoodLapin;
    }
}
//renvoie nv de nourriture du renard (pour verifier si reproduction possible)
int Animal::getNourriture() const {
    return food;
}

void Animal::setNourriture(int value) {
    food = value;
}




ostream& operator<<(ostream& out, Animal animal) {
    animal.affiche(out);
    return out;
}



//lucia
//etape 3

// constructeur par defaut
Population::Population() = default;

//réserve nouvel identifiant
int Population::reserve() {
    while (animaux.count(prochainId)) {
        ++prochainId;
    }
    return prochainId++;
}

//ajoute un animal dans la population
void Population::set(const Animal& a) {
    animaux[a.getId()] = a;
}

//supprime un animal à partir de son identifiant
void Population::supprime(int id) {
    animaux.erase(id);
}

//accès modifiable
Animal& Population::get(int id) {
    if (!animaux.count(id)) {
        throw std::out_of_range("Identifiant introuvable");
    }
    return animaux.at(id);
}

//accès constant
const Animal& Population::get(int id) const {
    if (!animaux.count(id)) {
        throw std::out_of_range("Identifiant introuvable");
    }
    return animaux.at(id);
}

//liste de tous les identifiants
std::vector<int> Population::getIds() const {
    std::vector<int> ids;
    for (const auto& pair : animaux) {
        ids.push_back(pair.first);
    }
    return ids;
}
//affiche nombre de lapins et renards à chaque tour de simulation
int Population::nbLapins() const {
    int n = 0;
    for (const auto& pair : animaux) {
        if (pair.second.getEspece() == Espece::Lapin) n++;
    }
    return n;
}

int Population::nbRenards() const {
    int n = 0;
    for (const auto& pair : animaux) {
        if (pair.second.getEspece() == Espece::Renard) n++;
    }
    return n;
}

//etape 4
Grille::Grille() {
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            tableau[i][j] = -1; // -1 = case vide
        }
    }
}

bool Grille::caseVide(Coord c) const {
    return tableau[c.getLigne()][c.getColonne()] == -1;
}
///donne id de l'animal à la case vide
int Grille::getCase(Coord c) const {
    return tableau[c.getLigne()][c.getColonne()];
}
//met son id dans une case
void Grille::setCase(Coord c, int id) {
    tableau[c.getLigne()][c.getColonne()] = id;
}
// vide la case
void Grille::videCase(Coord c) {
    tableau[c.getLigne()][c.getColonne()] = -1;
}




//etape 5

Jeu::Jeu() {}

//ajoute un animal dans la population et le place dans la grille
void Jeu::ajouteAnimal(Espece espece, Coord coord) {
    int id = population.reserve();                //demande un nouvel ID
    Animal a(id, espece, coord);                  //crée animal
    population.set(a);                            //ajoute animal
    grille.setCase(coord, id);                    //place l’animal dans la grille
}

//constructeur aléatoire avec probabilités
Jeu::Jeu(double probaLapin, double probaRenard) {
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            //on tire un nb entre 0 et 1
            double tirage = static_cast<double>(rand()) / RAND_MAX;
            
            Coord c(i, j);
            
            if (tirage < probaLapin) {
                ajouteAnimal(Espece::Lapin, c);//si tirage< proba lapin,on pllace un lapin
                
            } else if (tirage < probaLapin + probaRenard) {
                ajouteAnimal(Espece::Renard, c);//on place un renard
            }
        }//si case vide,on ne fait rien
    }
}

//vérifie la cohérence grille/population
void Jeu::verifieGrille() const {
    for (int id : population.getIds()) {
        const Animal& a = population.get(id);
        Coord pos = a.getCoord();
        if (grille.getCase(pos) != id) {
            throw std::runtime_error("Incohérent : animal " + std::to_string(id) + "pas à sa place dans la grille.");
        }
    }
}

//Q10
std::vector<Coord> Jeu::voisinsVides(Coord c) const {
    std::vector<Coord> vides;

    //récupère tt les coordonnées voisines
    Ensemble voisines = c.voisines();

    for (int i = 0; i < voisines.cardinal(); ++i) {
        Coord voisin = Coord(voisines.get(i));
        if (grille.caseVide(voisin)) {
            vides.push_back(voisin);
        }
    }

    return vides;
}


//Q11
//retourne les coord voisines de c occupées par un animal
std::vector<Coord> Jeu::voisinsEspece(Coord c, Espece espece) const {
    std::vector<Coord> resultats; //liste des voisins correspondant à l'espèce

    // récupère les coordonnées voisines de la case c
    Ensemble voisines = c.voisines(); //méthode de Coord

    //parcourt toutes les cases voisines
    for (int i = 0; i < voisines.cardinal(); ++i) {
        Coord voisin = Coord(voisines.get(i)); //conversion depuis int

        //la case n’est pas vide
        if (!grille.caseVide(voisin)) {
            int id = grille.getCase(voisin);       // on récupère l'id de l'animal
            const Animal& a = population.get(id);  // on récupère l'animal dans la population

            //son espèce correspond à celle cherchée on garde cette cooord
            if (a.getEspece() == espece) {
                resultats.push_back(voisin);
            }
        }
    }

    return resultats; //la liste des coordonnées
}


//Q12
void Jeu::deplaceAnimal(int id) {
    Animal& a = population.get(id);       // récupanimal
    Coord ancienne = a.getCoord();        //Coord actuelle

    std::vector<Coord> vides = voisinsVides(ancienne);  //cases vides autour

    if (!vides.empty()) {
        Coord nouvelle = vides[rand() % vides.size()];  //choix aléatoire

        grille.videCase(ancienne);     //vide ancienne case
        a.setCoord(nouvelle);          //déplace animal
        grille.setCase(nouvelle, id);  //place animal dans nouvelle case
    }
}

//projet
//affichage
void Jeu::afficheTexte() const {
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            Coord c(i, j);
            if (grille.caseVide(c)) cout << ".";
            else {
                int id = grille.getCase(c);
                Espece e = population.get(id).getEspece();
                cout << (e == Espece::Lapin ? "L" : "R");
            }
        }
        cout << endl;
    }
    cout << "==========================" << endl;
}



//lapins et renards

//lapins et renards

void Jeu::etape() {
    //etape 1
    //lapins
    std::vector<int> ids = population.getIds(); //recupere liste des id des animaux
    
    for (int id : ids) { //parcourt chaque animal
        Animal& a = population.get(id);
        
        //ignorer animaux morts ou non-lapins
        if (a.getEspece() != Espece::Lapin || a.estMort()) continue;
        
        Coord pos = a.getCoord();
        
        //récupère les cases vides autour avant déplacement
        std::vector<Coord> libres = voisinsVides(pos);
        
        //reproduction
        bool reproduit = false;
        if (libres.size() >= MinFreeBirthLapin) {
            double tirage = static_cast<double>(rand()) / RAND_MAX;
            if (tirage < ProBirthLapin) {
                reproduit = true;
            }
        }
        
        // déplacement
        if (!libres.empty()) {
            Coord cible = libres[rand() % libres.size()];
            a.setCoord(cible);
            grille.setCase(cible, id);
            grille.videCase(pos);
        }
        
        //naissance à l'ancienne position
        if (reproduit) {
            ajouteAnimal(Espece::Lapin, pos); //naît à l’ancienne position
        }
    }
    
    // etape 2
    // renards
    
    std::vector<int> ids2 = population.getIds();  // récupère les identifiants
    
    for (int id : ids2) {
        if (!population.getIds().empty() && !grille.caseVide(population.get(id).getCoord())) {
            Animal& a = population.get(id);
            
            if (a.getEspece() != Espece::Renard || a.estMort()) continue; // ignore les morts ou non-renards
            
            Coord pos = a.getCoord();
            
            // renard vieillit (perd 1 de nourriture)
            a.jeune();
            
            // s’il meurt de faim
            if (a.estMort()) {
                grille.videCase(pos);
                population.supprime(id);
                continue;
            }
            
            Coord nouvellePos = pos;
            bool aMange = false;
            std::vector<Coord> lapins = voisinsEspece(pos, Espece::Lapin);
            
            if (!lapins.empty()) {
                nouvellePos = lapins[rand() % lapins.size()];
                int lapinId = grille.getCase(nouvellePos);
                population.supprime(lapinId);  // mange le lapin
                a.mange();
                population.set(a);                     // gagne de la nourriture
                aMange = true;
                // Cap le niveau de nourriture à MaxFood
                if (a.getNourriture() > MaxFood) {
                    a.setNourriture(MaxFood);
                }
                
            } else {
                // sinon essaie une case vide
                std::vector<Coord> libres = voisinsVides(pos);
                if (!libres.empty()) {
                    nouvellePos = libres[rand() % libres.size()];
                }
            }
            
            // déplacement
            if (nouvellePos != pos) {
                grille.videCase(pos);
                a.setCoord(nouvellePos);
                grille.setCase(nouvellePos, id);
                population.set(a); //met à jour la nv position dans la population
            }
            
            // reproduction du renard (si assez nourri)
            if (aMange && a.getNourriture() >= FoodReprod) {
                double tirage = static_cast<double>(rand()) / RAND_MAX;
                if (tirage < ProBirthRenard) {
                    ajouteAnimal(Espece::Renard, pos);  // naissance à l’ancienne position
                }
            }
        }
    }
}

const Population& Jeu::getPopulation() const {
        return population;
    }

const Grille& Jeu::getGrille() const {
        return grille;
    }

void Jeu::exportPPM(std::string nomFichier) const {
    std::ofstream fichier(nomFichier); // ouvre fichier en écriture
    fichier << "P3\n";                         // format texte ppm
    fichier << TAILLEGRILLE << " " << TAILLEGRILLE << "\n";
    fichier << "255\n";                        // valeur max RGB

    for (int i = 0; i < TAILLEGRILLE; ++i) {
        for (int j = 0; j < TAILLEGRILLE; ++j) {
            Coord c(i, j);
            if (grille.caseVide(c)) {
                fichier << "255 255 255 ";     // blanc = vide
            } else {
                int id = grille.getCase(c);
                Espece e = population.get(id).getEspece();
                if (e == Espece::Lapin)
                    fichier << "0 255 0 ";     // vert = lapin
                else
                    fichier << "255 0 0 ";     // rouge = renard
            }
        }
        fichier << "\n";
    }
    fichier.close();  // ferme le fichier
}
