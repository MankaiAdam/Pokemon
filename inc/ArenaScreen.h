#ifndef POKEMON_ARENASCREEN_H
#define POKEMON_ARENASCREEN_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "PokemonAttack.h"

class ArenaScreen : public GameState
{
    sf::RenderWindow& window;
    PokemonParty* playerParty;

    PokemonAttack* playerTeam;
    PokemonAttack* enemyTeam;

    // Background
    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    // Pokemon textures and sprites
    std::vector<sf::Texture> playerTextures;
    std::vector<sf::Texture> enemyTextures;

    std::vector<sf::Sprite> playerSprites;
    std::vector<sf::Sprite> enemySprites;

    sf::Texture currentPlayerTexture;
    sf::Texture currentEnemyTexture;
    sf::Sprite currentPlayerSprite;
    sf::Sprite currentEnemySprite;

    // Font
    sf::Font pokemonFont;

    // Text
    sf::Text arenaText;
    sf::Text playerPokemonText;
    sf::Text enemyPokemonText;
    sf::Text currentPlayerNameText;
    sf::Text currentEnemyNameText;

    sf::Text playerHpText;
    sf::Text enemyHpText;

    sf::Texture attackButtonTexture;
    sf::Sprite attackButton;
    sf::Text attackText;

    // Current Pokemon fighting
    int playerPokemonIndex;
    int enemyPokemonIndex;

public:

    ArenaScreen(
        GameStateMachine* gameStateMachine,
        sf::RenderWindow& window,
        PokemonAttack* playerTeam,
        PokemonParty* playerParty
    );

    bool run();

private:
    void createEnemyTeam();
    void loadSprites();
    void setupTexts();
    void setupPokemonSprites();
    void updateCurrentPokemonSprites();

    void attack();
    void updateHpTexts();

    void draw();
    void handleClick(sf::Vector2i mousePosition);
};

#endif