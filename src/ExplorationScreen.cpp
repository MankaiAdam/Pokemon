#include "../inc/ExplorationScreen.h"

#include <iostream>

#include "GameStateMachine.h"
#include "Pokedex.h"
#include "SelectionScreen.h"
#include "../inc/EncounterScreen.h"


ExplorationScreen::ExplorationScreen(GameStateMachine* gameStateMachine,sf::RenderWindow& window, PokemonParty* playerParty)
    : GameState(gameStateMachine), window(window), playerParty(playerParty)
{
    loadSprites();
    setupTexts();
}


static sf::Sprite loadSpriteFromFile(
    std::string path,
    sf::Texture& texture)
{
    if (!texture.loadFromFile(path))
    {
        std::cout << "Impossible de charger : "
                  << path << std::endl;

        return sf::Sprite();
    }

    std::cout << path << " loaded" << std::endl;

    return sf::Sprite(texture);
}


template <typename T>
static void centerDrawable(
    T* drawable,
    const sf::RenderWindow& window,
    bool centerX,
    bool centerY)
{
    sf::FloatRect bounds = drawable->getGlobalBounds();

    sf::Vector2f position = drawable->getPosition();

    if (centerX)
        position.x =
            (window.getSize().x - bounds.width) / 2.0f;

    if (centerY)
        position.y =
            (window.getSize().y - bounds.height) / 2.0f;

    drawable->setPosition(position);
}


void ExplorationScreen::loadSprites()
{
    // Arriere Plan
    std::string path =
        "../data/images/exploration.png";

    sf::Sprite sprite =
        loadSpriteFromFile(path, bg_texture);

    if (sprite.getTexture() != nullptr)
    {
        sf::FloatRect size =
            sprite.getLocalBounds();

        float scale =
            window.getSize().y / size.height;

        sprite.setScale(scale, scale);

        bg_sprite = sprite;

        centerDrawable(
            &bg_sprite,
            window,
            true,
            true
        );
    }


    // Boutton Explorer
    path =
        "../data/images/Button200.png";

    sprite =
        loadSpriteFromFile(
            path,
            exploreButtonTexture
        );

    if (sprite.getTexture() != nullptr)
    {
        float width =
            sprite.getLocalBounds().width;

        float scale =
            200.0f / width;

        sprite.setScale(scale, scale);

        exploreButton = sprite;

        centerDrawable(
            &exploreButton,
            window,
            true,
            false
        );

        exploreButton.setPosition(
            exploreButton.getPosition().x,
            650
        );
    }
}


void ExplorationScreen::setupTexts()
{
    if (!PokemonFrlgFont.loadFromFile(
        "../data/pokemon-frlg.otf"))
    {
        std::cout
            << "Impossible de charger la police."
            << std::endl;
    }
    if (!PokemonFont.loadFromFile(
            "../data/pokemon.ttf"))
    {
        std::cout
            << "Impossible de charger la police."
            << std::endl;
    }


    //Titre Exploration
    explorationText.setFont(PokemonFont);
    explorationText.setString("EXPLORATION");
    explorationText.setCharacterSize(80);
    explorationText.setFillColor(sf::Color::White);

    centerDrawable(&explorationText, window,true,false);
    explorationText.setPosition(explorationText.getPosition().x,250);


    //Texte Boutton Explorer
    exploreBtnText.setFont(PokemonFrlgFont);
    exploreBtnText.setString("EXPLORER");
    exploreBtnText.setCharacterSize(40);
    exploreBtnText.setFillColor(sf::Color::White);

    centerDrawable(&exploreBtnText, window,true,false);
    exploreBtnText.setPosition(exploreBtnText.getPosition().x,660);
}


void ExplorationScreen::handleClick(
    sf::Vector2i mousePosition)
{
    if (exploreButton.getGlobalBounds().contains(mousePosition.x,mousePosition.y))
    {
        std::cout << "EXPLORE clicked" << std::endl;

        int randomEvent = rand() % 10;

        if (randomEvent < 6)
        {
            // 60% chance: Rencontre Pokemon
            int randomId = 1 + rand() % 151;

            Pokedex& pokedex = Pokedex::getInstance();

            Pokemon* pokemon =
                pokedex.clonePokemon(randomId);

            gameStateMachine->setGameState(
                std::make_unique<EncounterScreen>(
                    gameStateMachine,
                    window,
                    pokemon,
                    playerParty
                )
            );
        }
        else
        {
            // 40% chance: Arena

            gameStateMachine->setGameState(
                std::make_unique<SelectionScreen>(
                    gameStateMachine,
                    window,
                    playerParty
                )
            );
        }
    }
}


void ExplorationScreen::draw()
{
    window.clear(sf::Color(100, 100, 100));

    window.draw(bg_sprite);

    window.draw(explorationText);

    window.draw(exploreButton);
    window.draw(exploreBtnText);

    window.display();
}


bool ExplorationScreen::run()
{
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }

            if (event.type ==
                sf::Event::MouseButtonPressed)
            {
                handleClick(
                    sf::Mouse::getPosition(window)
                );
                return true;
            }
        }

        draw();
    }

    return true;
}