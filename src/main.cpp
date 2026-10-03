#include <iostream>
#include <SFML/Graphics.hpp>

#include "GameStateMachine.h"
#include "Pokemon.h"
#include "Pokedex.h"
#include "PokemonParty.h"
#include "PokemonAttack.h"
#include "SelectionScreen.h"
#include "MenuScreen.h"

int main() {

    /*Pokedex& pokedex = Pokedex::getInstance();

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

    return 0;*/


    sf::RenderWindow window(sf::VideoMode(1100, 800),"Pokemon The Game",sf::Style::Fullscreen);

    /*
    for (int i = 1; i <= 30; i++)
    {
        pokemons[i]->displayInfo();
    }*/

    //SelectionScreen selection(window, pokemons);
    //selection.run();


    GameStateMachine gameStateMachine(window);

    //MenuScreen mainMenu(gameStateMachine, window);
    //mainMenu.run();

    gameStateMachine.run();

    return 0;
}