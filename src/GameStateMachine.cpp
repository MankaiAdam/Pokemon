#include "GameStateMachine.h"

#include "MenuScreen.h"
#include "../inc/ExplorationScreen.h"

GameStateMachine::GameStateMachine(sf::RenderWindow& window, PokemonParty* playerParty) : playerParty(playerParty)
{
    game_state = std::make_unique<MenuScreen>(this, window, playerParty);
}

void GameStateMachine::setGameState(std::unique_ptr<GameState> gameState)
{
    game_state = std::move(gameState);
}

void GameStateMachine::run()
{
    while (game_state != nullptr)
    {
        if (!game_state->run())
            break;
    }
}
