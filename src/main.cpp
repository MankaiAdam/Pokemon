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

    sf::RenderWindow window(sf::VideoMode(1100, 800),"Pokemon The Game",sf::Style::Fullscreen);

    //creation ddu party avec un starter Pokemon
    PokemonParty playerParty;
    Pokedex& pokedex = Pokedex::getInstance();
    Pokemon* starter = pokedex.clonePokemon(6);
    playerParty.add(starter);

    GameStateMachine gameStateMachine(window, &playerParty);

    gameStateMachine.run();

    return 0;
}