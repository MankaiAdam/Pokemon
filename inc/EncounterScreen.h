#ifndef POKEMON_ENCOUNTERSCREEN_H
#define POKEMON_ENCOUNTERSCREEN_H

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "Pokemon.h"
#include "PokemonParty.h"

class EncounterScreen : public GameState
{
    const float CONTENT_Y_OFFSET = 150.0f;
private:
    sf::RenderWindow& window;
    PokemonParty* playerParty;

    Pokemon* pokemon;

    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    sf::Texture pokemonTexture;
    sf::Sprite pokemonSprite;

    sf::Texture buttonTexture;
    sf::Sprite catchButton;

    sf::Font pokemonFont;
    sf::Text encounterText;
    sf::Text pokemonNameText;
    sf::Text catchText;
    sf::Text resultText;

public:
    EncounterScreen(GameStateMachine* gameStateMachine, sf::RenderWindow& window, Pokemon* pokemon, PokemonParty* playerParty);

    bool run();

private:
    void loadSprites();
    void setupTexts();
    void draw();
    void handleClick(sf::Vector2i mousePosition);
};

#endif // POKEMON_ENCOUNTERSCREEN_H