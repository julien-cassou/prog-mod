#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "coord.hpp"

    //coord

TEST_CASE("construction valide") {
    Coord c(10, 15);
    CHECK(c.getLigne() == 10);
    CHECK(c.getColonne() == 15);
}

TEST_CASE( "ligne hors borne") {
    CHECK_THROWS_AS(Coord(-1, 10), out_of_range);
    CHECK_THROWS_AS(Coord(40, 10), out_of_range);
}

TEST_CASE("colonne hors borne") {
    CHECK_THROWS_AS(Coord(10, -2), out_of_range);
    CHECK_THROWS_AS(Coord(10, 100), out_of_range);
    CHECK_THROWS_AS(Coord(TAILLEGRILLE, TAILLEGRILLE), out_of_range);
}

TEST_CASE("une coordonnée") {
    Coord c(5, 10);
}

TEST_CASE("getters coord") {
    Coord c(3, 6);
    CHECK(c.getLigne() == 3);
    CHECK(c.getColonne() == 6);
}

TEST_CASE("ligne hors borne") {
    CHECK_THROWS_AS(Coord(-1, 10), out_of_range);
    CHECK_THROWS_AS(Coord(40, 10), out_of_range);
}

TEST_CASE("colonne hors borne") {
    CHECK_THROWS_AS(Coord(5, -1), out_of_range);
    CHECK_THROWS_AS(Coord(5, 40), out_of_range);
}

TEST_CASE("Affichage Coord") {
    Coord c(1, 2);
    ostringstream oss;
    oss << c;
    CHECK(oss.str() == "(1,2)");
}

TEST_CASE("operateur == et !=") {
    Coord c(1,2);
    Coord d(3,4);
    CHECK(c == Coord (1,2));
    CHECK(c != d);
    CHECK(Coord (0,0) == Coord (0,0));
}

TEST_CASE("toInt & constructeur à partir d'un entier") {
    CHECK(Coord(5,4).toInt() == 204);
    CHECK(Coord (0,0).toInt() == 0);
    Coord d {204};
    CHECK(d.getColonne() == 4);
    CHECK(d.getLigne() == 5);
}

    // Ensemble

TEST_CASE("cardinal") {
    Ensemble t;
    t.nouvelle_ensemble(5);
    CHECK(t.cardinal() == 5);
    t.ajoute(9);
    CHECK(t.cardinal() == 6);
    Ensemble e;
    CHECK(e.cardinal() == 0);
}

TEST_CASE("estVide") {
    Ensemble t;
    t.nouvelle_ensemble(5);
    CHECK_FALSE(t.estVide());
    Ensemble e;
    CHECK(e.estVide());
}

TEST_CASE("ajoute") {
    Ensemble e;
    e.nouvelle_ensemble(MAXCARD);
    CHECK_THROWS_AS(e.ajoute(4), runtime_error);
    Ensemble t;
    t.ajoute(1);
    CHECK(t.cardinal() == 1);
}

TEST_CASE("tire" ) {
    Ensemble e;
    CHECK_THROWS_AS(e.tire(), runtime_error);
    Ensemble j;
    j.nouvelle_ensemble(5);
    j.tire();
    CHECK(j.cardinal() == 4);
    Ensemble p;
    p.nouvelle_ensemble(1);
    p.tire();
    CHECK(p.estVide());
}

TEST_CASE("voisines") {
    Coord c1 = Coord(0,0);
    Coord c2 = Coord(TAILLEGRILLE - 1,TAILLEGRILLE - 1);
    Coord c3 = Coord(0,TAILLEGRILLE - 1);
    Coord c4 = Coord(TAILLEGRILLE - 1,0);
    Coord c5 = Coord(3,4);
    Coord c6 = Coord(4,3);
    Ensemble e1 = c1.voisines();
    CHECK(e1.cardinal() == 3);
    ostringstream os;
    e1.affiche(os);
    CHECK(os.str() == "(0,1) (1,0) (1,1) ");
    Ensemble e2 = c2.voisines();
    CHECK(e2.cardinal() == 3);
    ostringstream oss;
    e2.affiche(oss);
    CHECK(oss.str() == "(38,38) (38,39) (39,38) ");
    Ensemble e3 = c3.voisines();
    CHECK(e3.cardinal() ==3);
    Ensemble e4 = c4.voisines();
    CHECK(e4.cardinal() == 3);
    Ensemble e5 = c5.voisines();
    CHECK(e5.cardinal() == 8);
    Ensemble e6 = c6.voisines();
    CHECK(e6.cardinal() == 8);
}

TEST_CASE("Ensemble de coords voisines") {
	Coord w {3,4};
	Ensemble e;
	e = w.voisines();
	while(!e.estVide()) {
		int b = e.tire();
		Coord c{b};
		cout << c << " ";
	}

    cout << endl;
	Coord n {3,39};
	Ensemble l;
	l = n.voisines();
	while(!l.estVide()){
		int b = l.tire();
		Coord c{b};
		cout << c << " ";
	}

}
