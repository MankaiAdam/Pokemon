#include "SelectionScreen.h"
#include <iostream>

#include "GameStateMachine.h"
#include "MenuScreen.h"
#include "../inc/ArenaScreen.h"

SelectionScreen::SelectionScreen(GameStateMachine* gameStateMachine, sf::RenderWindow& window, PokemonParty* playerParty)
    :GameState(gameStateMachine), window(window), playerParty(playerParty)
{
    /*
    Pokedex& pokedex = Pokedex::getInstance();

    for (int i = 1; i <= 30; i++)
    {
        Pokemon* pokemon = pokedex.clonePokemon(i);
        pokemon->displayInfo();
        pokemons.push_back(pokemon);
    }
     */
    if (playerParty != nullptr)
    {
        pokemons = playerParty->getPokemons();
    }

    loadSprites();
    setupTexts();
}

static int getIdFromName(std::vector<std::string> vector, std::string name) {
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i] == name)
            return i;
    }
    return -1;
}

static bool loadTexturesFromFile(std::string path, std::vector<sf::Texture>& textures) {

    sf::Texture texture;

    if (!texture.loadFromFile(path))
    {
        std::cout << "Impossible de charger : "
                  << path << std::endl;
        return false;
    }
    std::cout<<path<<" loaded"<<std::endl;
    textures.push_back(texture);
    return true;
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
    textures.reserve(1+1+1+1);
    typeTextures.reserve(POKEMONS_TYPES.size());
    pokemonSprites.reserve(pokemons.size());

    //sprites des pokemons
    for (auto pokemon : pokemons)
    {
        std::string path =
            "../data/images/pokemons/" +
            std::to_string(pokemon->getId()) +
            ".png";

        sf::Texture texture;

        if (!texture.loadFromFile(path))
        {
            std::cout << "Impossible de charger : "
                      << path << std::endl;
            pokemonSprites.push_back(sf::Sprite());
            continue;
        }
        std::cout<<path<<" loaded"<<std::endl;
        spritesTextures[pokemon->getId()] = texture;

        sf::Sprite sprite = sf::Sprite(spritesTextures[pokemon->getId()]);

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

    //sprites des types
    for (auto type : POKEMONS_TYPES)
    {
        std::string path = "../data/images/types/Type_" + type + ".png";

        if (!loadTexturesFromFile(path, typeTextures)) {
            continue;
        }
    }
    std::cout << typeTextures.size() << " textures loaded" << std::endl;

    //arriere plan selection
    std::string path = "../data/images/selection_box.png";

    sf::Sprite sprite = loadSpriteFromFile(path, textures);
    if (sprite.getTexture() != nullptr)
    {
        float width = sprite.getLocalBounds().width;
        float scale = selectionBoxWidth / width;
        sprite.setScale(scale, scale);
        selectionBox = sprite;
    }
    selectionBox.setPosition(pokemonsSelectionOffset.x, pokemonsSelectionOffset.y);

    //arriere plan selectionnés
    path = "../data/images/selected_box.png";

    sprite = loadSpriteFromFile(path, textures);
    if (sprite.getTexture() != nullptr)
    {
        float width = sprite.getLocalBounds().width;
        float scale = selectionBoxWidth / width;
        sprite.setScale(scale, scale);
        selectedBox = sprite;
    }
    selectedBox.setPosition(pokemonsSelectedOffset.x, pokemonsSelectedOffset.y);

    //pokemons selecetionés
    sf::Vector2i offset = {pokemonsSelectedOffset.x + 30 ,pokemonsSelectedOffset.y + 30};
    for (int i = 0; i <  selectedPokemonsSprites.size(); i++){
        float width = selectedPokemonsSprites[i].getLocalBounds().width;
        float scale = spriteSize / width;
        sprite.setScale(scale, scale);
        selectedPokemonsSprites[i].setPosition(offset.x,offset.y);
        offset.x += spriteSize;
    }

    //arriere plan info
    path = "../data/images/info_box.png";

    sprite = loadSpriteFromFile(path, textures);
    if (sprite.getTexture() != nullptr)
    {
        float width = sprite.getLocalBounds().width;
        float scale = infoBoxWidth / width;
        sprite.setScale(scale, scale);
        infoBox = sprite;
    }
    infoBox.setPosition(pokemonsInfoOffset.x, pokemonsInfoOffset.y);

    //Bouton Confirmer
    path = "../data/images/Button200.png";

    sprite = loadSpriteFromFile(path, textures);
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
    titleText.setCharacterSize(60);
    titleText.setPosition(700, 50);

    counterText.setFont(PokemonFrlgFont);
    counterText.setCharacterSize(25);
    counterText.setPosition(800, 150);

    int x = pokemonsInfoOffset.x + 50;
    int y = pokemonsInfoOffset.y + 20;

    PokemonNameText.setFont(PokemonFrlgFont);
    PokemonNameText.setCharacterSize(60);
    PokemonNameText.setFillColor(sf::Color::Black);
    PokemonNameText.setPosition(x, y);

    PokemonHPText.setFont(PokemonFrlgFont);
    PokemonHPText.setCharacterSize(40);
    PokemonHPText.setFillColor(sf::Color::Black);
    PokemonHPText.setPosition(x, y + 140);

    PokemonAttackText.setFont(PokemonFrlgFont);
    PokemonAttackText.setCharacterSize(40);
    PokemonAttackText.setFillColor(sf::Color::Black);
    PokemonAttackText.setPosition(x, y + 220);

    PokemonDefenseText.setFont(PokemonFrlgFont);
    PokemonDefenseText.setCharacterSize(40);
    PokemonDefenseText.setFillColor(sf::Color::Black);
    PokemonDefenseText.setPosition(x, y + 300);

    PokemonEvolutionText.setFont(PokemonFrlgFont);
    PokemonEvolutionText.setCharacterSize(40);
    PokemonEvolutionText.setFillColor(sf::Color::Black);
    PokemonEvolutionText.setPosition(x, y + 380);

    confirmButton.setPosition(1300, 900);

    confirmText.setFont(PokemonFrlgFont);
    confirmText.setString("CONFIRMER");
    confirmText.setCharacterSize(30);
    confirmText.setFillColor(sf::Color::White);
    confirmText.setOutlineColor(sf::Color(70, 70, 70));
    confirmText.setOutlineThickness(3);
    confirmText.setPosition(1330, 913);
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

void SelectionScreen::updateSelectedUI() {
    for (int i = 0;i < selectedPokemons.size();i++){
        auto pokemon = selectedPokemons[i];
        selectedPokemonsSprites[i].setTexture(spritesTextures.at(pokemon->getId()));
        selectedPokemonsSprites[i].setColor(sf::Color(255,255,255,255));
    }
    for (int i = selectedPokemons.size();i < selectedPokemonsSprites.size();i++){
        selectedPokemonsSprites[i].setColor(sf::Color(255,255,255,0));
    }
}

void SelectionScreen::handleClick(sf::Vector2i mousePosition)
{
    // Vérifier si on a cliqué sur un Pokémon
    for (size_t i = 0; i < pokemonSprites.size(); i++)
    {
        int row = i / columns;
        int column = i % columns;

        float x = pokemonsSelectionOffset.x + column * (spriteSize + spacing);
        float y = pokemonsSelectionOffset.y + row * (spriteSize + spacing);

        sf::FloatRect box(
            x,
            y,
            spriteSize,
            spriteSize
        );

        if (box.contains(
            static_cast<float>(mousePosition.x),
            static_cast<float>(mousePosition.y)))
        {
            Pokemon* pokemon = pokemons[i];

            // Si déjà sélectionné > retirer
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
                updateSelectedUI();
            }
            // Sinon > ajouter si moins de 6
            else if (selectedPokemons.size() < 6)
            {
                selectedPokemons.push_back(pokemon);
                updateSelectedUI();

            }

            return;
        }
    }

    // Bouton confirmer
    if (confirmButton.getGlobalBounds().contains(
        static_cast<float>(mousePosition.x),
        static_cast<float>(mousePosition.y)))
    {
        if (selectedPokemons.size() > 0)
        {
            PokemonAttack* attackTeam = new PokemonAttack();
            for (auto pokemon : selectedPokemons)
                attackTeam->add(pokemon);
            gameStateMachine->setGameState(std::make_unique<ArenaScreen>(gameStateMachine, window, attackTeam, playerParty));
        }
    }
}

void SelectionScreen::handleMove(sf::Vector2i mousePosition)
{
    // Vérifier si on a survolé  sur un Pokémon
    for (size_t i = 0; i < pokemonSprites.size(); i++)
    {
        int row = i / columns;
        int column = i % columns;

        float x = pokemonsSelectionOffset.x + column * (spriteSize + spacing);
        float y = pokemonsSelectionOffset.y + row * (spriteSize + spacing);

        sf::FloatRect box(
            x,
            y,
            spriteSize,
            spriteSize
        );

        if (box.contains(mousePosition.x,mousePosition.y)) {
            Pokemon* pokemon = pokemons[i];
            PokemonNameText.setString(pokemon->getName());
            PokemonHPText.setString("HitPoints : " + std::to_string((int)pokemon->getMaxHp()));
            PokemonAttackText.setString("Attaque : " +std::to_string((int)pokemon->getAttack()));
            PokemonDefenseText.setString("Defense : " +std::to_string((int)pokemon->getDefense()));
            PokemonEvolutionText.setString("Evolution : " +std::to_string(pokemon->getEvolution()));

            std::string type1 = pokemon->getType1();
            std::string type2 = pokemon->getType2();
            std::cout << "types : "<< type1 << " - " << type2 << std::endl;

            if (type1.compare("") != 0) {
                PokemonType1.setTexture(typeTextures[getIdFromName(POKEMONS_TYPES, type1)]);
                PokemonType2.setColor(sf::Color(255, 255, 255, 255));
            }else
                PokemonType1.setColor(sf::Color(255, 255, 255, 0));

            if (type2.compare("") != 0){
                PokemonType2.setTexture(typeTextures[getIdFromName(POKEMONS_TYPES, type2)]);
                PokemonType2.setColor(sf::Color(255, 255, 255, 255));
            }else
                PokemonType2.setColor(sf::Color(255, 255, 255, 0));

            float height = PokemonType1.getLocalBounds().height;
            float scale = typeSpriteHeight / height;
            PokemonType1.setScale(scale, scale);
            PokemonType1.setPosition(pokemonsInfoOffset.x + 50, pokemonsInfoOffset.y + 100);

            height = PokemonType2.getLocalBounds().height;
            scale = typeSpriteHeight / height;
            PokemonType2.setScale(scale, scale);
            PokemonType2.setPosition(
                pokemonsInfoOffset.x + 50 + PokemonType1.getGlobalBounds().width + 10,
                pokemonsInfoOffset.y + 100
            );

            return;
        }else {
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

    window.draw(selectionBox);
    window.draw(selectedBox);
    window.draw(infoBox);
    window.draw(counterText);
    window.draw(PokemonNameText);
    window.draw(PokemonHPText);
    window.draw(PokemonAttackText);
    window.draw(PokemonDefenseText);
    window.draw(PokemonEvolutionText);
    window.draw(PokemonType1);
    window.draw(PokemonType2);
    for (auto pokemon :  selectedPokemonsSprites){
        window.draw(pokemon);
    }

    // Pokémon
    for (size_t i = 0; i < pokemonSprites.size(); i++)
    {
        int row = i / columns;
        int column = i % columns;

        float x = pokemonsSelectionOffset.x + column * (spriteSize + spacing);
        float y = pokemonsSelectionOffset.y + row * (spriteSize + spacing);

        // Sprite
        sf::FloatRect bounds = pokemonSprites[i].getLocalBounds();

        if (isSelected(pokemons[i]))
            pokemonSprites[i].setColor(sf::Color(255, 255, 255, 100));
        else
            pokemonSprites[i].setColor(sf::Color(255, 255, 255, 255));

        pokemonSprites[i].setPosition(
            x + (spriteSize - bounds.width * pokemonSprites[i].getScale().x) / 2,
            y + 10
        );

        window.draw(pokemonSprites[i]);
    }

    // Bouton confirmer
    if (selectedPokemons.size() > 0)
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
                return true;
            }
            if (event.type == sf::Event::MouseMoved)
            {
                handleMove(
                    sf::Vector2i(
                        event.mouseMove.x,
                        event.mouseMove.y
                    )
                );
            }
        }

        draw();
    }

    return true;
}