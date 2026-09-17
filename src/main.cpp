#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pokemon.h"
#include "Pokedex.h"
#include "PokemonParty.h"
#include "PokemonAttack.h"

int main() {

    Pokedex& pokedex = Pokedex::getInstance();

    std::cout << "*** test Pokedex ***" << std::endl;

    Pokemon pikachu = pokedex.cloneByName("Pikachu");

    pikachu.displayInfo();

    std::cout << "*** test Party ***"<< std::endl;

    PokemonParty party;

    party.add(new Pokemon(pokedex.cloneByName("Pikachu")));
    party.add(new Pokemon(pokedex.cloneByName("Charizard")));
    party.add(new Pokemon(pokedex.cloneByName("Gengar")));

    std::cout << "taille Party: " << party.getSize() << std::endl;

    // extraire un Pokemon
    Pokemon* extracted = party.extractByName("Charizard");

    if (extracted != nullptr)
    {
        std::cout << "Extrait: " << extracted->getName() << std::endl;
        extracted->displayInfo();
    }

    std::cout << "taille Party apres extraction: " << party.getSize() << std::endl;

    std::cout << "*** test group Attack ***" << std::endl;

    PokemonAttack attack;

    attack.add(extracted);

    std::cout << "Pokemon ajoute au group attack."<< std::endl;


    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello SFML");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}