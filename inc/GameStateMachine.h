#ifndef POKEMON_GAMESTATEMACHINE_H
#define POKEMON_GAMESTATEMACHINE_H
#include <SFML/Graphics/RenderWindow.hpp>

#include "PokemonParty.h"

class GameState;

class GameStateMachine
{
    GameState* game_state;
    PokemonParty* playerParty;
public:
    GameStateMachine(sf::RenderWindow& window, PokemonParty* playerParty);
    void setGameState(GameState* gameState);
    void run();
};


#endif
