#ifndef POKEMON_GAMESTATEMACHINE_H
#define POKEMON_GAMESTATEMACHINE_H
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "PokemonParty.h"

class GameState;

class GameStateMachine
{
    std::unique_ptr<GameState> game_state;
    PokemonParty* playerParty;
public:
    GameStateMachine(sf::RenderWindow& window, PokemonParty* playerParty);
    void setGameState(std::unique_ptr<GameState> gameState);
    void run();
};


#endif
