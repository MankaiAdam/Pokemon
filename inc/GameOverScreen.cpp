#include "GameOverScreen.h"

#include <iostream>

GameOverScreen::GameOverScreen(
    GameStateMachine* gameStateMachine,
    sf::RenderWindow& window
)
    : GameState(gameStateMachine),
      window(window)
{
    loadSprites();
    setupTexts();
}

void GameOverScreen::loadSprites()
{
    if (!bgTexture.loadFromFile("../data/images/exploration.png"))
    {
        std::cerr << "Error loading game over background\n";
    }

    bgSprite.setTexture(bgTexture);

    float scaleX =
        static_cast<float>(window.getSize().x) /
        bgTexture.getSize().x;

    float scaleY =
        static_cast<float>(window.getSize().y) /
        bgTexture.getSize().y;

    bgSprite.setScale(scaleX, scaleY);
}

void GameOverScreen::setupTexts()
{
    if (!pokemonFont.loadFromFile("../data/pokemon.ttf"))
    {
        std::cerr << "Error loading Pokemon font\n";
    }

    gameOverText.setFont(pokemonFont);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::Red);

    sf::FloatRect bounds =
        gameOverText.getLocalBounds();

    gameOverText.setOrigin(
        bounds.left + bounds.width / 2.0f,
        bounds.top + bounds.height / 2.0f
    );

    gameOverText.setPosition(
        window.getSize().x / 2.0f,
        window.getSize().y / 2.0f
    );
}

void GameOverScreen::handleClick()
{
    window.close();
}

void GameOverScreen::draw()
{
    window.clear();

    window.draw(bgSprite);
    window.draw(gameOverText);

    window.display();
}

bool GameOverScreen::run()
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

            if (event.type == sf::Event::MouseButtonPressed)
            {
                handleClick();
                return false;
            }
        }

        draw();
    }

    return false;
}