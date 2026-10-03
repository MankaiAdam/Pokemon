#include "GameStateMachine.h"

#include "MenuScreen.h"

GameStateMachine::GameStateMachine(sf::RenderWindow& window)
{
    game_state = new MenuScreen(this, window);
}

void GameStateMachine::setGameState(GameState* gameState)
{
    game_state = gameState;
}

void GameStateMachine::run()
{
    while (game_state != nullptr)
    {
        if (!game_state->run())
            break;
    }
}
