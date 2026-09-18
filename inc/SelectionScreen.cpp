#include "../src/SelectionScreen.h"
#include <iostream>
#include <sstream>

SelectionScreen::SelectionScreen(sf::RenderWindow& window,
                                 const std::vector<Pokemon*>& pokemons)
    : window(window), pokemons(pokemons)
{
    loadSprites();
    setupTexts();
}

static sf::Sprite loadSpriteFromFile(std::string path, std::vector<sf::Texture>& textures) {

    sf::Texture texture;

    if (!texture.loadFromFile(path))
    {
        std::cout << "Impossible de charger : "
                  << path << std::endl;

        return sf::Sprite();
    }
    std::cout<<path<<" loaded"<<std::endl;
    textures.push_back(texture);

    sf::Sprite sprite = sf::Sprite(textures.back());
    return sprite;
}

void SelectionScreen::loadSprites()
{
    textures.reserve(pokemons.size()+1);
    pokemonSprites.reserve(pokemons.size());
    for (Pokemon* pokemon : pokemons)
    {
        std::string path =
            "../data/images/pokemons/" +
            std::to_string(pokemon->getId()) +
            ".png";

        sf::Sprite sprite = loadSpriteFromFile(path, textures);

        if (sprite.getTexture() == nullptr) {
            //std::cout << "pas de texture" << std::endl;
            pokemonSprites.push_back(sf::Sprite());
            continue;
        }

        // Adapter le sprite à la taille de la case
        float width = sprite.getLocalBounds().width;
        float height = sprite.getLocalBounds().height;

        float scale = std::min(
            spriteSize / width,
            spriteSize / height
        );

        sprite.setScale(scale, scale);

        pokemonSprites.push_back(sprite);
    }

    //sprites des typess

    std::string path = "../data/images/Button200.png";

    sf::Sprite sprite = loadSpriteFromFile(path, textures);
    if (sprite.getTexture() != nullptr)
    {
        float width = sprite.getLocalBounds().width;
        float scale = 180 / width;
        sprite.setScale(scale, scale);
        confirmButton = sprite;
    }


}


void SelectionScreen::setupTexts()
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

    titleText.setFont(PokemonFrlgFont);
    titleText.setString("CHOISISSEZ VOTRE EQUIPE");
    titleText.setCharacterSize(32);
    titleText.setPosition(300, 20);

    counterText.setFont(PokemonFrlgFont);
    counterText.setCharacterSize(22);
    counterText.setPosition(800, 150);

    //confirmButton.setSize(sf::Vector2f(180, 50));
    confirmButton.setPosition(850, 720);

    confirmText.setFont(PokemonFrlgFont);
    confirmText.setString("CONFIRMER");
    confirmText.setCharacterSize(30);
    confirmText.setPosition(880, 733);

    confirmText.setFillColor(sf::Color::White);
    confirmText.setOutlineColor(sf::Color(70, 70, 70));
    confirmText.setOutlineThickness(3);
}


bool SelectionScreen::isSelected(Pokemon* pokemon) const
{
    for (Pokemon* selected : selectedPokemons)
    {
        if (selected == pokemon)
        {
            return true;
        }
    }

    return false;
}


void SelectionScreen::handleClick(sf::Vector2i mousePosition)
{
    // Vérifier si on a cliqué sur un Pokémon
    for (size_t i = 0; i < pokemonSprites.size(); i++)
    {
        int row = i / columns;
        int column = i % columns;

        float x = 30 + column * (boxSize + spacing);
        float y = 130 + row * (boxSize + spacing);

        sf::FloatRect box(
            x,
            y,
            boxSize,
            boxSize
        );

        if (box.contains(
            static_cast<float>(mousePosition.x),
            static_cast<float>(mousePosition.y)))
        {
            Pokemon* pokemon = pokemons[i];

            // Si déjà sélectionné → retirer
            if (isSelected(pokemon))
            {
                for (auto it = selectedPokemons.begin();
                     it != selectedPokemons.end();
                     ++it)
                {
                    if (*it == pokemon)
                    {
                        selectedPokemons.erase(it);
                        break;
                    }
                }
            }
            // Sinon → ajouter si moins de 6
            else if (selectedPokemons.size() < 6)
            {
                selectedPokemons.push_back(pokemon);
            }

            return;
        }
    }

    // Bouton confirmer
    if (confirmButton.getGlobalBounds().contains(
        static_cast<float>(mousePosition.x),
        static_cast<float>(mousePosition.y)))
    {
        if (selectedPokemons.size() == 6)
        {
            // Pour l'instant on ferme simplement l'écran.
            // On connectera cela à PokemonAttack ensuite.
            window.close();
        }
    }
}


void SelectionScreen::draw()
{
    window.clear(sf::Color(100, 100, 100));

    window.draw(titleText);

    // Compteur
    counterText.setString(
        "Equipe : " +
        std::to_string(selectedPokemons.size()) +
        " / 6"
    );

    window.draw(counterText);

    // Pokémon
    for (size_t i = 0; i < pokemonSprites.size(); i++)
    {
        int row = i / columns;
        int column = i % columns;

        float x = 30 + column * (boxSize + spacing);
        float y = 130 + row * (boxSize + spacing);

        // Case
        /*sf::RectangleShape box;
        box.setSize(sf::Vector2f(boxSize, boxSize));
        box.setPosition(x, y);

        if (isSelected(pokemons[i]))
        {
            box.setFillColor(sf::Color(180, 220, 180));
            box.setOutlineThickness(4);
            box.setOutlineColor(sf::Color(50, 150, 50));
        }
        else
        {
            box.setFillColor(sf::Color::White);
            box.setOutlineThickness(2);
            box.setOutlineColor(sf::Color(180, 180, 180));
        }

        window.draw(box);*/

        // Sprite
        sf::FloatRect bounds = pokemonSprites[i].getLocalBounds();

        if (isSelected(pokemons[i]))
            pokemonSprites[i].setColor(sf::Color(255, 255, 255, 100));
        else
            pokemonSprites[i].setColor(sf::Color(255, 255, 255, 255));

        pokemonSprites[i].setPosition(
            x + (boxSize - bounds.width * pokemonSprites[i].getScale().x) / 2,
            y + 10
        );

        window.draw(pokemonSprites[i]);

        // ID
        /*sf::Text idText;
        idText.setFont(font);
        idText.setString(
            "#" + std::to_string(pokemons[i]->getId())
        );
        idText.setCharacterSize(14);
        idText.setPosition(x + 8, y + 95);

        window.draw(idText);*/
    }

    // Bouton confirmer
    if (selectedPokemons.size() == 6)
    {
        confirmButton.setColor(sf::Color(255, 255, 255, 255));
        confirmText.setFillColor(sf::Color(255, 255, 255, 255));
        confirmText.setOutlineColor(sf::Color(70, 70, 70,255));
    }
    else
    {
        confirmButton.setColor(sf::Color(255, 255, 255, 125));
        confirmText.setFillColor(sf::Color(255, 255, 255, 125));
        confirmText.setOutlineColor(sf::Color(70, 70, 70, 125));
    }

    window.draw(confirmButton);
    window.draw(confirmText);

    window.display();
}


bool SelectionScreen::run()
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

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                handleClick(
                    sf::Vector2i(
                        event.mouseButton.x,
                        event.mouseButton.y
                    )
                );
            }
        }

        draw();
    }

    return true;
}