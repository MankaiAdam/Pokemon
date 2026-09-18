#ifndef SELECTIONSCREEN_H
#define SELECTIONSCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Pokemon.h"
#include "PokemonAttack.h"

class SelectionScreen {
private:
    const int MAX_POKEMONS = PokemonAttack::MAX_POKEMONS;

    sf::RenderWindow& window;

    std::vector<Pokemon*> pokemons;
    std::vector<Pokemon*> selectedPokemons;

    std::vector<sf::Texture> textures;
    std::vector<sf::Sprite> pokemonSprites;

    sf::Font PokemonFont;
    sf::Font PokemonFrlgFont;
    sf::Text PokemonNameText;
    sf::Sprite PokemonType1;
    sf::Sprite PokemonType2;
    sf::Sprite confirmButton;
    sf::Text confirmText;
    sf::Text titleText;
    sf::Text counterText;

    int columns = 6;
    int boxSize = 100;
    int spriteSize = 100;
    int spacing = 0;

public:
    SelectionScreen(sf::RenderWindow& window,
                    const std::vector<Pokemon*>& pokemons);

    bool run();

private:
    void loadSprites();
    void setupTexts();
    void draw();
    void handleClick(sf::Vector2i mousePosition);

    bool isSelected(Pokemon* pokemon) const;
};

#endif