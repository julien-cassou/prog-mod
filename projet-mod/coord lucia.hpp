
#ifndef COORD_HPP
#define COORD_HPP

#include <stdexcept>
#include <ostream>
#include <vector>
#include <unordered_map>
using namespace std;


const int MAXCARD = 1600;
const int TAILLEGRILLE = 40;

enum class Espece {Lapin, Renard};

const float ProBirthLapin = 0.30;
const int MinFreeBirthLapin = 4;
const float ProBirthRenard = 0.05;

const int FoodInit = 5;
const int FoodLapin = 5;
const int FoodReprod = 8;
const int MaxFood = 10;


class Ensemble {
    
private:
    int t[MAXCARD];
    int card;
public:
    Ensemble();
    int cardinal() const;
    bool estVide() const;
    void ajoute(int entier);
    int tire();
    int get(int i) const;
    void affiche(ostream& out) const;
    void nouvelle_ensemble(int taille);
    friend ostream &operator<<(ostream& out, const Ensemble& e);
};


class Coord {
private:
    int ligne;
    int colonne;
public:
    Coord(int l, int c);
    Coord(int entier);
    int getLigne() const;
    int getColonne() const;
    Ensemble voisines() const;
    friend ostream &operator<<(ostream& os, const Coord& c);
    friend bool operator==(const Coord& a, const Coord& b);
    friend bool operator!=(const Coord& a, const Coord& b);
};


class Animal {
public:
    Animal();
    Animal(int id, Espece espece, Coord coord);

    int getId() const;
    Coord getCoord() const;
    void setCoord(Coord c);
    Espece getEspece() const;
    int getNourriture() const; //renard
    void setNourriture(int value); //modifier le niveau de nourriture du renard
    ostream& affiche(ostream &out) const;
    

    bool estMort() const;
    bool seReproduit(int nbvoisin) const;

    void mange();
    void jeune();

private:
    int id;
    Espece espece;
    Coord coord;
    int food;
};

ostream& operator<<(ostream& out, Espece espece);
ostream& operator<<(ostream& out, Animal animal);


class Population {
private:
    std::unordered_map<int, Animal> animaux;
    int prochainId = 0;

public:
    Population();

    int reserve();
    void set(const Animal& a);
    void supprime(int id);

    Animal& get(int id);
    const Animal& get(int id) const;

    std::vector<int> getIds() const;
    
    int nbLapins() const;
    int nbRenards() const;
};


class Grille {
private:
    int tableau[TAILLEGRILLE][TAILLEGRILLE];

public:
    Grille();

    bool caseVide(Coord c) const;
    int getCase(Coord c) const;
    void videCase(Coord c);
    void setCase(Coord c, int id);
};


class Jeu {
private:
    Grille grille;
    Population population;

public:
    Jeu();
    Jeu(double probaLapin, double probaRenard);

    void ajouteAnimal(Espece espece, Coord coord);
    
    void verifieGrille() const;
    std::vector<Coord> voisinsVides(Coord c) const;
    std::vector<Coord> voisinsEspece(Coord c, Espece espece) const;
    void deplaceAnimal(int id);//Q12
    
    void etape();           // exécute un tour de jeu
    void afficheTexte() const; // affichage console

    // Pour les tests
    const Population& getPopulation() const;
    const Grille& getGrille() const;
    
    // exporte une image ppm de la grille
    void exportPPM(std::string nomFichier) const; // exporte une image .ppm de la grille
};

#endif 
