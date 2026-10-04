#ifndef POKEMON_MENUSCREEN_H
#define POKEMON_MENUSCREEN_H

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "PokemonParty.h"

class MenuScreen : public GameState
{
    sf::RenderWindow& window;
    PokemonParty* playerParty;

    sf::Texture bg_texture;
    sf::Sprite bg_sprite;
    sf::Text menu_text;

    sf::Font PokemonFont;
    sf::Font PokemonFrlgFont;

    int bgHeight;

public:
    MenuScreen(GameStateMachine* gameStateMachine,sf::RenderWindow& w, PokemonParty* playerParty);

    bool run();

private:
    void loadSprites();
    void setupTexts();
    void draw();
    void handleClick();
};

#endif //POKEMON_MENUSCREEN_H