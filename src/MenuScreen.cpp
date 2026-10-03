#include "MenuScreen.h"

#include <iostream>

#include "GameStateMachine.h"
#include "SelectionScreen.h"

MenuScreen::MenuScreen(GameStateMachine* gameStateMachine, sf::RenderWindow& window)
    :GameState(gameStateMachine) ,window(window)
{
    loadSprites();
    setupTexts();
}

static sf::Sprite loadSpriteFromFile(std::string path, sf::Texture& texture) {


    if (!texture.loadFromFile(path))
    {
        std::cout << "Impossible de charger : "
                  << path << std::endl;

        return sf::Sprite();
    }
    std::cout<<path<<" loaded"<<std::endl;

    sf::Sprite sprite = sf::Sprite(texture);
    return sprite;
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
        position.x = (window.getSize().x - bounds.width) / 2.0f;

    if (centerY)
        position.y = (window.getSize().y - bounds.height) / 2.0f;

    drawable->setPosition(position);
}

void MenuScreen::loadSprites()
{
    //arriere plan selection
    std::string path = "../data/images/main_menu.png";

    sf::Sprite sprite = loadSpriteFromFile(path, bg_texture);
    if (sprite.getTexture() != nullptr)
    {
        sf::FloatRect size = sprite.getLocalBounds();
        float scale = window.getSize().y / size.height;
        sprite.setScale(scale, scale);
        bg_sprite = sprite;
        centerDrawable(&bg_sprite, window , true, true);
    }
}


void MenuScreen::setupTexts()
{
    //charger la police pokemon
    if (!PokemonFont.loadFromFile("../data/pokemon.ttf"))
    {
        std::cout << "Impossible de charger la police." << std::endl;
    }
    if (!PokemonFrlgFont.loadFromFile("../data/pokemon-frlg.otf"))
    {
        std::cout << "Impossible de charger la police." << std::endl;
    }

    menu_text.setFont(PokemonFrlgFont);
    menu_text.setString("Press any Key");
    menu_text.setCharacterSize(60);
    centerDrawable(&menu_text, window , true, true);
    menu_text.setFillColor(sf::Color::White);
}




void MenuScreen::handleClick()
{
    //menu_text.setColor(sf::Color::Black);
    gameStateMachine->setGameState(new SelectionScreen(gameStateMachine, window));
}

void MenuScreen::draw()
{
    window.clear(sf::Color(100, 100, 100));

    window.draw(bg_sprite);
    window.draw(menu_text);

    window.display();
}


bool MenuScreen::run()
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

            if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed)
            {
                handleClick();
                return true;
            }
        }

        draw();
    }

    return true;
}