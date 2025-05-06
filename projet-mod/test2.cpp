#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Jeu.hpp"

    // Espece

TEST_CASE("affichage espèce") {
    ostringstream out;
    out << Espece::Renard;
    CHECK(out.str() == "Renard");
    ostringstream os;
    os << Espece::Lapin;
    CHECK(os.str() == "Lapin");
}

    // Animal

TEST_CASE("constructeur & accesseurs") {
    Animal a = {23, Espece::Renard, Coord (1,2), FoodInit, AgeInit};
    CHECK(a.getId() == 23);
    CHECK(a.getCoord() == Coord (1,2));
    a.setCoord(Coord (3,4));
    CHECK(a.getCoord() == Coord (3,4));
}

TEST_CASE("estMort & jeune/vieillesse") {
    Animal b = {3, Espece::Renard, Coord (6,13), FoodInit, AgeInit};
    CHECK_FALSE(b.estMort());
    for(int i = 1; i <= 5; i++) { b.jeune();}
    CHECK(b.estMort());
    Animal a = {2, Espece::Lapin, Coord{3,19}, FoodInit, AgeInit};
    for (int j = 1; j < 26; j++) a.vieilli();
    CHECK(b.estMort());
    Animal c = {4, Espece::Renard, Coord{4,19}, FoodInit, AgeInit};
    for (int j = 1; j < 31; j++) c.vieilli();
    CHECK(c.estMort());
}

TEST_CASE("mange") {
    Animal b = {3, Espece::Renard, Coord (6,13), FoodInit, AgeInit};
    for(int i = 1; i <= 5; i++) { b.jeune();}
    b.mange();
    CHECK_FALSE(b.estMort());
    Animal a = {2, Espece::Lapin, Coord (5,13), FoodInit, AgeInit};
    CHECK_THROWS_AS(a.mange(), runtime_error);
}

TEST_CASE("affichage Animal") {
    Animal a = {2, Espece::Lapin, Coord (5,13), FoodInit, AgeInit};
    ostringstream os;
    os << a;
    CHECK(os.str() == "Animal: 2, Lapin, (5,13), 0");
    Animal b = {3, Espece::Renard, Coord (6,13), FoodInit, AgeInit};
    ostringstream oss;
    oss << b;
    CHECK(oss.str() == "Animal: 3, Renard, (6,13), 0, 5");
}

    // Population

TEST_CASE("Population::reserve") {
    Population p;
    int id1 = p.reserve();
    CHECK(id1 == 1600);
    int id2 = p.reserve();
    CHECK(id2 == 1599);
}

TEST_CASE("Population::set") {
    Population p;
    int id = 1600;
    Animal a = {0, Espece::Lapin, Coord(4, 0), FoodInit, AgeInit};
    p.set(a);
    CHECK(p.get(id).getId() == 1600);
    CHECK(p.get(id).getEspece() == Espece::Lapin);
    CHECK(p.get(id).getCoord() == Coord(4,0));
    Animal b = {-1, Espece::Renard, Coord(4, 1), FoodInit, AgeInit};
    p.set(b);
    int id2 = 1599;
    CHECK(p.get(id2).getId() == 1599);
    CHECK(p.get(id2).getEspece() == Espece::Renard);
    CHECK(p.get(id2).getCoord() == Coord(4,1));
}

TEST_CASE("Population::supprime") {
    Population p;
    Animal a = {0, Espece::Lapin, Coord(0, 0), FoodInit, AgeInit};
    p.set(a);
    int id = 1600;
    p.supprime(id);
    CHECK_THROWS_AS(p.get(id), runtime_error);
}

TEST_CASE("Population::getIds") {
    Population p;
    int id1 = 1600;
    int id2 = 1599;
    Animal a = {0, Espece::Lapin, Coord(0, 0), FoodInit, AgeInit};
    Animal b = {0, Espece::Lapin, Coord(1, 0), FoodInit, AgeInit};
    p.set(a);
    p.set(b);
    Ensemble ids = p.getIds();
    CHECK(ids.cardinal() == 2);
    CHECK(id1 == MAXCARD);
    CHECK(id2 == MAXCARD - 1);
}

    // Grille

TEST_CASE("Test fonctions grille") {
    Grille g;
    Coord c(2, 3);
    g.setCase(c, 42);
    CHECK_FALSE(g.CaseVide(c));              
    CHECK(g.getCase(c) == 42);
    g.setCase(c, 15);
    g.VideCase(c);
    CHECK(g.CaseVide(c));                 
    CHECK(g.getCase(c) == 0);
}

    // Jeu

TEST_CASE("Test ajout et déplacement d'animaux") {
    Jeu temp(0.0, 0.0); 
    Coord c1(1, 1);
    
    // Ajout d'un animal
    temp.ajouteAnimal(Espece::Lapin, c1);
    // Déplacement de l'animal
    temp.DeplaceAnimal(1600);
    temp.DeplaceAnimal(1600);
    temp.DeplaceAnimal(1600);
    Population p = temp.getPopulation();
    Animal a = p.get(1600);
    CHECK(a.getAge() == 3);
    CHECK_NOTHROW(temp.Coherence());
}

TEST_CASE("Test vérification de la grille") {
    Jeu temp(0.0, 0.0);
    CHECK_NOTHROW(temp.verifieGrille()); 

    Coord c(0, 0);
    temp.ajouteAnimal(Espece::Lapin, c);
    CHECK_NOTHROW(temp.verifieGrille()); 
}

TEST_CASE("case pleine") {
    Jeu jeu(0.0, 0.0);
    Coord c(2, 2);
    jeu.ajouteAnimal(Espece::Lapin, c);
    CHECK_THROWS_AS(jeu.ajouteAnimal(Espece::Lapin, c), runtime_error);
}

TEST_CASE("mort renard affamé") {
    Animal r(0, Espece::Renard, Coord(1, 1), FoodInit, AgeInit);
    for (int i = 0; i < 12; ++i) r.jeune();
    CHECK(r.estMort());

    Jeu jeu(0.0, 0.0);
    Coord c(3,3);
    jeu.ajouteAnimal(Espece::Renard, c);
    for (int i = 1; i <= 5; i++) jeu.DeplaceAnimal(1600);
    Population pop = jeu.getPopulation();
    CHECK_THROWS_AS(pop.get(1600);, runtime_error);
}