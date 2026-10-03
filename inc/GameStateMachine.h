#ifndef POKEMON_GAMESTATEMACHINE_H
#define POKEMON_GAMESTATEMACHINE_H
#include <SFML/Graphics/RenderWindow.hpp>

class GameState;

class GameStateMachine
{
    GameState* game_state;
public:
    GameStateMachine(sf::RenderWindow& window);
    void setGameState(GameState* gameState);
    void run();
};


#endif
