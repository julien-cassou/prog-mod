//
//  test.cpp
//  coordonées
//

//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../coord.hpp"

//tests pour les lapins
TEST_CASE("Lapin se déplace") {
    Jeu jeu;
    Coord c(5, 5);
    jeu.ajouteAnimal(Espece::Lapin, c);
    int id = jeu.getGrille().getCase(c);

    CHECK(id != -1); // Vérifie que l’animal a bien été ajouté

    jeu.etape(); // Un tour de simulation

    Coord nouvellePos = jeu.getPopulation().get(id).getCoord();

    CHECK(nouvellePos != c); // Le lapin s’est déplacé
    CHECK(jeu.getGrille().getCase(nouvellePos) == id); // Nouvelle case occupée par le même lapin
    CHECK(jeu.getGrille().caseVide(c)); // Ancienne case libérée
}

TEST_CASE("Lapin se reproduit") {
    Jeu jeu;
    Coord c(10, 10);
    jeu.ajouteAnimal(Espece::Lapin, c);

    (void)jeu.getGrille().getCase(c);
    int id = jeu.getGrille().getCase(c);
    CHECK(id != -1);
    

    bool reproduced = false;

    //répète plusieurs étapes pour que la proba reussise
    for (int i = 0; i < 20; ++i) {
        jeu.etape();
        if (jeu.getPopulation().getIds().size() > 1) {
            reproduced = true;
            break;
        }
    }

    CHECK(reproduced);  //au moins un nouveau lapin né
}

TEST_CASE("Lapin ne meurt jamais") {
    Jeu jeu;
    Coord c(7, 7);
    jeu.ajouteAnimal(Espece::Lapin, c);

    (void)jeu.getGrille().getCase(c);

    //50 tours
    for (int i = 0; i < 50; ++i) {
        jeu.etape();
        //lapin initial (descendants) doivent toujours exister
        CHECK_FALSE(jeu.getPopulation().getIds().empty());
    }
}

//tests pour les renards
TEST_CASE("Renard meurt de faim") {
    Jeu jeu;
    Coord c(5, 5);
    jeu.ajouteAnimal(Espece::Renard, c);
    int id = jeu.getGrille().getCase(c);

    for (int i = 0; i < 5; ++i) {
        jeu.etape(); //il perd 1 de nourriture
    }

    CHECK(jeu.getPopulation().getIds().empty()); //renard est mort
    CHECK(jeu.getGrille().caseVide(c));          // case vide
}

TEST_CASE("Renard mange un lapin") {
    Jeu jeu;

    Coord lapinPos(10, 11);
    Coord renardPos(10, 10);

    jeu.ajouteAnimal(Espece::Lapin, lapinPos);
    jeu.ajouteAnimal(Espece::Renard, renardPos);

    int idRenard = jeu.getGrille().getCase(renardPos);
    Animal& r = jeu.getPopulation().get(idRenard);

    int idLapin = jeu.getGrille().getCase(lapinPos);
    CHECK(idLapin != -1);

    jeu.etape(); // Le renard doit manger le lapin voisin

    CHECK(jeu.getGrille().caseVide(lapinPos)); // La case du lapin est vide
    CHECK(r.getCoord() == lapinPos);           // Le renard est à la place du lapin
}

TEST_CASE("Reproduction renard") {
    Jeu jeu;
    Coord c(15, 15);
    jeu.ajouteAnimal(Espece::Renard, c);
    int id = jeu.getGrille().getCase(c);

    Animal& r = jeu.getPopulation().get(id);

    // Nourrir suffisamment le renard
    for (int i = 0; i < 5; ++i) {
        r.mange();
    }
    jeu.getPopulation().set(r); // Met à jour la population

    CHECK(r.getNourriture() >= FoodReprod); // Condition minimale pour reproduction

    bool reproduced = false;

    for (int i = 0; i < 30; ++i) {
        jeu.etape(); // Plusieurs étapes pour compenser la probabilité
        if (jeu.getPopulation().getIds().size() > 1) {
            reproduced = true;
            break;
        }
    }

    CHECK(reproduced); // Vérifie qu'un nouveau renard est né
}
