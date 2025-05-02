#include <iostream>
#include "SFML/Graphics.hpp"

int main() {
    // Créer une fenêtre de 800x600 pixels avec le titre "Test SFML"
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test SFML");

    // Créer un cercle blanc de rayon 50
    sf::CircleShape lapin(50);
    lapin.setFillColor(sf::Color::White);
    lapin.setPosition(375, 275); // centré approximativement

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Fermer la fenêtre si on clique sur la croix
        }

        window.clear(sf::Color::Black); // Efface la fenêtre (fond noir)
        window.draw(lapin);             // Dessine le cercle
        window.display();               // Affiche le rendu à l'écran
    }

    return 0;
}

