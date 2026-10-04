#include "../inc/EncounterScreen.h"

#include <iostream>

#include "GameStateMachine.h"
#include "ExplorationScreen.h"

EncounterScreen::EncounterScreen(
    GameStateMachine* gameStateMachine,
    sf::RenderWindow& window,
    Pokemon* pokemon,
    PokemonParty* playerParty)
    : GameState(gameStateMachine),
      window(window),
      pokemon(pokemon),
      playerParty(playerParty)
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
    sf::FloatRect bounds =
        drawable->getGlobalBounds();

    sf::Vector2f position =
        drawable->getPosition();

    if (centerX)
        position.x =
            (window.getSize().x - bounds.width) / 2.0f;

    if (centerY)
        position.y =
            (window.getSize().y - bounds.height) / 2.0f;

    drawable->setPosition(position);
}


void EncounterScreen::loadSprites()
{
    // Arriere Plan
    std::string path =
        "../data/images/exploration.png";

    bgSprite =
        loadSpriteFromFile(path, bgTexture);

    if (bgSprite.getTexture() != nullptr)
    {
        sf::FloatRect size =
            bgSprite.getLocalBounds();

        float scale =
            window.getSize().y / size.height;

        bgSprite.setScale(scale, scale);

        centerDrawable(
            &bgSprite,
            window,
            true,
            true
        );
    }


    // Pokémon
    if (pokemon != nullptr)
    {
        path =
            "../data/images/pokemons/" +
            std::to_string(pokemon->getId()) +
            ".png";

        pokemonSprite =
            loadSpriteFromFile(
                path,
                pokemonTexture
            );

        if (pokemonSprite.getTexture() != nullptr)
        {
            float width =
                pokemonSprite.getLocalBounds().width;

            float height =
                pokemonSprite.getLocalBounds().height;

            float scale =
                std::min(
                    250.0f / width,
                    250.0f / height
                );

            pokemonSprite.setScale(
                scale,
                scale
            );

            centerDrawable(
                &pokemonSprite,
                window,
                true,
                false
            );

            pokemonSprite.setPosition(
                pokemonSprite.getPosition().x,
                180.0f + CONTENT_Y_OFFSET
            );
        }
    }

    // Boutton capturer
    path =
        "../data/images/Button200.png";

    buttonTexture.loadFromFile(path);

    catchButton =
        sf::Sprite(buttonTexture);

    auto width =
        catchButton.getLocalBounds().width;

    float scale =
        180.0f / width;

    catchButton.setScale(scale, scale);

    centerDrawable(&catchButton, window, true, false);
    catchButton.setPosition(
        catchButton.getPosition().x,
        600.0f + CONTENT_Y_OFFSET
    );
}


void EncounterScreen::setupTexts()
{
    if (!pokemonFont.loadFromFile(
        "../data/pokemon-frlg.otf"))
    {
        std::cout
            << "Impossible de charger la police."
            << std::endl;
    }


    //Titre
    encounterText.setFont(pokemonFont);
    encounterText.setString("Tu rencontres un Pokemon.!");
    encounterText.setCharacterSize(50);
    encounterText.setFillColor(sf::Color::White);

    centerDrawable(
        &encounterText,
        window,
        true,
        false
    );

    encounterText.setPosition(
        encounterText.getPosition().x,
        40.0f + CONTENT_Y_OFFSET
    );


    // Nom Pokémon
    pokemonNameText.setFont(pokemonFont);
    pokemonNameText.setCharacterSize(40);
    pokemonNameText.setFillColor(sf::Color::White);

    if (pokemon != nullptr)
    {
        pokemonNameText.setString(
            pokemon->getName()
        );
    }

    centerDrawable(
        &pokemonNameText,
        window,
        true,
        false
    );

    pokemonNameText.setPosition(
        pokemonNameText.getPosition().x,
        450.0f + CONTENT_Y_OFFSET
    );


    // Boutton Capturer Texte
    catchText.setFont(pokemonFont);
    catchText.setString("Capturer");
    catchText.setCharacterSize(40);
    catchText.setFillColor(sf::Color::White);

    centerDrawable(
        &catchText,
        window,
        false,
        false
    );

    centerDrawable(&catchText, window, true, false);
    catchText.setPosition(
        catchText.getPosition().x,
        600.0f + CONTENT_Y_OFFSET
    );

    resultText.setFont(pokemonFont);
    resultText.setCharacterSize(45);
    resultText.setFillColor(sf::Color::White);
}


void EncounterScreen::handleClick(
    sf::Vector2i mousePosition)
{
    float x =
        static_cast<float>(mousePosition.x);

    float y =
        static_cast<float>(mousePosition.y);


    // Boutton capturer
    if (catchButton.getGlobalBounds().contains(x, y))
    {
        std::cout
            << "Catch clicked"
            << std::endl;

        bool captured = false;

        if (pokemon != nullptr)
        {
            int hp = pokemon->getMaxHp();

            int captureChance = 100 - hp / 2;
            captureChance = std::max(std::min(captureChance,90),10);

            int randomNumber = std::rand() % 100;

            std::cout << "Capture chance : "
                      << captureChance << "%" << std::endl;

            std::cout << "Random number : "
                      << randomNumber << std::endl;

            if (randomNumber < captureChance)
            {
                std::cout << "Pokemon captured!"
                          << std::endl;
                captured = true;

                if (playerParty != nullptr)
                {
                    playerParty->add(pokemon);
                    pokemon = nullptr;
                }
            }
            else
            {
                std::cout << "Pokemon escaped!"
                          << std::endl;
            }
        }

        resultText.setString(
            captured
                ? "Le Pokemon est capture"
                : "Le Pokemon s est echappe"
        );
        centerDrawable(
            &resultText,
            window,
            true,
            false
        );
        resultText.setPosition(
            resultText.getPosition().x,
            520.0f + CONTENT_Y_OFFSET
        );

        window.clear(sf::Color(100, 100, 100));
        window.draw(bgSprite);
        window.draw(encounterText);
        window.draw(pokemonSprite);
        window.draw(pokemonNameText);
        window.draw(resultText);
        window.display();

        sf::sleep(sf::seconds(2));

        gameStateMachine->setGameState(
            std::make_unique<ExplorationScreen>(
                gameStateMachine,
                window,
                playerParty
            )
        );

        return;

    }
}


void EncounterScreen::draw()
{
    window.clear(
        sf::Color(100, 100, 100)
    );

    window.draw(bgSprite);

    window.draw(encounterText);

    window.draw(pokemonSprite);

    window.draw(pokemonNameText);

    window.draw(catchButton);

    window.draw(catchText);

    if (!resultText.getString().isEmpty())
    {
        window.draw(resultText);
    }

    window.display();
}


bool EncounterScreen::run()
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