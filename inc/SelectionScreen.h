#ifndef SELECTIONSCREEN_H
#define SELECTIONSCREEN_H

#include <array>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Pokemon.h"
#include "PokemonAttack.h"

class SelectionScreen {
private:
    const int MAX_POKEMONS = PokemonAttack::MAX_POKEMONS;
    const std::vector<std::string> POKEMONS_TYPES = Pokemon::POKEMONS_TYPES;

    sf::RenderWindow& window;

    std::vector<Pokemon*> pokemons;
    std::vector<Pokemon*> selectedPokemons;

    std::unordered_map<int,sf::Texture> spritesTextures;
    std::vector<sf::Texture> textures;
    std::vector<sf::Texture> typeTextures;
    std::vector<sf::Sprite> pokemonSprites;

    sf::Font PokemonFont;
    sf::Font PokemonFrlgFont;
    sf::Text PokemonNameText;
    sf::Text PokemonHPText;
    sf::Text PokemonAttackText;
    sf::Text PokemonDefenseText;
    sf::Text PokemonEvolutionText;
    sf::Sprite PokemonType1;
    sf::Sprite PokemonType2;
    sf::Sprite selectionBox;
    sf::Sprite selectedBox;
    sf::Sprite infoBox;
    sf::Sprite confirmButton;
    std::array<sf::Sprite, 6> selectedPokemonsSprites;
    sf::Text confirmText;
    sf::Text titleText;
    sf::Text counterText;

    std::string hoveredPokemon;

    int columns = 6;
    sf::Vector2i pokemonsSelectionOffset = {300, 200};
    sf::Vector2i pokemonsSelectedOffset = {300, 920};
    sf::Vector2i pokemonsInfoOffset = {1200, 200};
    int selectionBoxWidth = 850;
    int infoBoxWidth = 377;
    int typeSpriteHeight = 30;
    int spriteSize = 140;
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
    void handleMove(sf::Vector2i mousePosition);
    void updateSelectedUI();

    bool isSelected(Pokemon* pokemon) const;
};

#endif