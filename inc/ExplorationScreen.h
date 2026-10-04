//
// Created by adam-mankai on 10/3/26.
//
#ifndef POKEMON_EXPLORATIONSCREEN_H
#define POKEMON_EXPLORATIONSCREEN_H

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "PokemonParty.h"

class ExplorationScreen : public GameState
{
private:
    sf::RenderWindow& window;
    PokemonParty* playerParty;

    sf::Texture bg_texture;
    sf::Sprite bg_sprite;

    sf::Texture exploreButtonTexture;
    sf::Sprite exploreButton;

    sf::Font PokemonFont;
    sf::Font PokemonFrlgFont;
    sf::Text explorationText;
    sf::Text exploreBtnText;

public:
    ExplorationScreen(GameStateMachine* gameStateMachine,
                      sf::RenderWindow& window,
                      PokemonParty* playerParty);

    bool run();

private:
    void loadSprites();
    void setupTexts();
    void draw();
    void handleClick(sf::Vector2i mousePosition);
};

#endif // POKEMON_EXPLORATIONSCREEN_H