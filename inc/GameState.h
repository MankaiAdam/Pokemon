#ifndef POKEMON_GAMESTATE_H
#define POKEMON_GAMESTATE_H

class GameStateMachine;

class GameState
{
protected:
    GameStateMachine* gameStateMachine;

    GameState(GameStateMachine* gameStateMachine);
public:

    virtual ~GameState() = default;

    virtual bool run() = 0;
};

#endif