#include "GameStateMachine.h"

#include "MenuScreen.h"
#include "../inc/ExplorationScreen.h"

GameStateMachine::GameStateMachine(sf::RenderWindow& window, PokemonParty* playerParty) : playerParty(playerParty)
{
    game_state = new MenuScreen(this, window, playerParty);
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
