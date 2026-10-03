#ifndef POKEMON_MENUSCREEN_H
#define POKEMON_MENUSCREEN_H

#include <SFML/Graphics.hpp>

#include "GameState.h"

class MenuScreen : public GameState
{
    sf::RenderWindow& window;
    sf::Texture bg_texture;
    sf::Sprite bg_sprite;
    sf::Text menu_text;

    sf::Font PokemonFont;
    sf::Font PokemonFrlgFont;

    int bgHeight;

public:
    MenuScreen(GameStateMachine* gameStateMachine,sf::RenderWindow& w);

    bool run();

private:
    void loadSprites();
    void setupTexts();
    void draw();
    void handleClick();
};

#endif //POKEMON_MENUSCREEN_H