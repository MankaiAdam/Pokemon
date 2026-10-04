#ifndef POKEMON_GAMEOVERSCREEN_H
#define POKEMON_GAMEOVERSCREEN_H

#include <SFML/Graphics.hpp>
#include "GameState.h"

class GameOverScreen : public GameState
{
    sf::RenderWindow& window;

    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    sf::Font pokemonFont;
    sf::Text gameOverText;

public:
    GameOverScreen(
        GameStateMachine* gameStateMachine,
        sf::RenderWindow& window
    );

    bool run();

private:
    void loadSprites();
    void setupTexts();
    void handleClick();
    void draw();
};

#endif