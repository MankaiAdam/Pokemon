#include "ArenaScreen.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "ExplorationScreen.h"
#include "GameOverScreen.h"
#include "GameStateMachine.h"
#include "Pokedex.h"

ArenaScreen::ArenaScreen(
    GameStateMachine* gameStateMachine,
    sf::RenderWindow& window,
    PokemonAttack* playerTeam,
    PokemonParty* playerParty
)
    : GameState(gameStateMachine),
      window(window),
      playerTeam(playerTeam),
      playerParty(playerParty)
{
    playerPokemonIndex = 0;
    enemyPokemonIndex = 0;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    createEnemyTeam();
    loadSprites();
    setupTexts();
    setupPokemonSprites();
    updateCurrentPokemonSprites();

    updateHpTexts();
}

void ArenaScreen::createEnemyTeam()
{
    enemyTeam = new PokemonAttack();

    const int teamSize = playerTeam->getSize();

    Pokedex& pokedex = Pokedex::getInstance();

    for (int i = 0; i < teamSize; i++)
    {
        int randomId = 1 + std::rand() % 151;

        Pokemon* pokemon = pokedex.clonePokemon(randomId);

        if (pokemon != nullptr)
        {
            enemyTeam->add(pokemon);
        }
    }
}

static sf::Sprite loadSpriteFromFile(
    std::string path,
    std::vector<sf::Texture>& textures)
{
    sf::Texture texture;

    if (!texture.loadFromFile(path))
    {
        std::cout << "Impossible de charger : "
                  << path << std::endl;

        return sf::Sprite();
    }

    std::cout << path << " loaded" << std::endl;

    textures.push_back(texture);

    return sf::Sprite(textures.back());
}

void ArenaScreen::loadSprites()
{
    // Arriere Plan
    if (!bgTexture.loadFromFile("../data/images/exploration.png"))
    {
        std::cerr << "Error loading arena background\n";
    }

    bgSprite.setTexture(bgTexture);

    sf::FloatRect size = bgSprite.getLocalBounds();
    float scale = window.getSize().y / size.height;
    bgSprite.setScale(scale, scale);


    // Boutton Attaque
    if (!attackButtonTexture.loadFromFile(
            "../data/images/Button200.png"))
    {
        std::cerr << "erreur texture boutton attaque\n";
    }

    attackButton.setTexture(attackButtonTexture);

    float buttonScale = 0.8f;

    attackButton.setScale(
        buttonScale,
        buttonScale
    );

    attackButton.setPosition(
        window.getSize().x / 2.0f - 80.0f,
        window.getSize().y - 120.0f
    );
}

void ArenaScreen::setupTexts()
{
    if (!pokemonFont.loadFromFile("../data/pokemon.ttf"))
    {
        std::cerr << "Error loading Pokemon font\n";
    }

    //Titre
    arenaText.setFont(pokemonFont);
    arenaText.setString("POKEMON ARENA");
    arenaText.setCharacterSize(50);
    arenaText.setFillColor(sf::Color::White);

    sf::FloatRect titleBounds =
        arenaText.getLocalBounds();

    arenaText.setOrigin(
        titleBounds.left +
            titleBounds.width / 2.0f,
        titleBounds.top +
            titleBounds.height / 2.0f
    );

    arenaText.setPosition(
        window.getSize().x / 2.0f,
        100.0f
    );


    // Titre Joueur
    playerPokemonText.setFont(pokemonFont);
    playerPokemonText.setString("JOUEUR");
    playerPokemonText.setCharacterSize(30);
    playerPokemonText.setFillColor(sf::Color::White);

    playerPokemonText.setPosition(
        80.0f,
        100.0f
    );

    currentPlayerNameText.setFont(pokemonFont);
    currentPlayerNameText.setCharacterSize(28);
    currentPlayerNameText.setFillColor(sf::Color::White);
    currentPlayerNameText.setPosition(240.0f, 220.0f);



    // Titre Ennemies
    enemyPokemonText.setFont(pokemonFont);
    enemyPokemonText.setString("ENNEMIES");
    enemyPokemonText.setCharacterSize(30);
    enemyPokemonText.setFillColor(sf::Color::White);

    enemyPokemonText.setPosition(
        window.getSize().x - 250.0f,
        100.0f
    );

    currentEnemyNameText.setFont(pokemonFont);
    currentEnemyNameText.setCharacterSize(28);
    currentEnemyNameText.setFillColor(sf::Color::White);
    currentEnemyNameText.setPosition(
        window.getSize().x - 350.0f,
        220.0f
    );



    //HP Joueur
    playerHpText.setFont(pokemonFont);
    playerHpText.setCharacterSize(22);
    playerHpText.setFillColor(sf::Color::White);

    playerHpText.setPosition(
        240.0f,
        300.0f
    );


    //HP n
    enemyHpText.setFont(pokemonFont);
    enemyHpText.setCharacterSize(22);
    enemyHpText.setFillColor(sf::Color::White);

    enemyHpText.setPosition(
        window.getSize().x - 360.0f,
        300.0f
    );


    // Boutton Attaque
    attackText.setFont(pokemonFont);
    attackText.setString("ATTACK");
    attackText.setCharacterSize(25);
    attackText.setFillColor(sf::Color::White);

    sf::FloatRect attackBounds =
        attackText.getLocalBounds();

    attackText.setOrigin(
        attackBounds.left +
            attackBounds.width / 2.0f,
        attackBounds.top +
            attackBounds.height / 2.0f
    );

    attackText.setPosition(
        attackButton.getPosition().x +
            attackButton.getGlobalBounds().width / 2.0f,

        attackButton.getPosition().y +
            attackButton.getGlobalBounds().height / 2.0f
    );
}

void ArenaScreen::setupPokemonSprites()
{
    playerTextures.reserve(6);
    enemyTextures.reserve(6);

    if (playerTeam == nullptr ||
        enemyTeam == nullptr)
    {
        return;
    }


    // Pokemons Joueur
    for (Pokemon* pokemon :
         playerTeam->getPokemons())
    {
        if (pokemon == nullptr)
        {
            continue;
        }

        std::string path =
            "../data/images/pokemons/" +
            std::to_string(pokemon->getId()) +
            ".png";

        sf::Sprite sprite =
            loadSpriteFromFile(
                path,
                playerTextures
            );

        if (playerTextures.empty())
        {
            continue;
        }

        float maxSize = static_cast<float>(
            std::max(
                playerTextures.back().getSize().x,
                playerTextures.back().getSize().y
            )
        );

        float scale = 70.0f / maxSize;

        sprite.setScale(
            scale,
            scale
        );

        float x = 60.0f;

        float y =
            150.0f +
            playerSprites.size() * 90.0f;

        sprite.setPosition(x, y);

        playerSprites.push_back(sprite);
    }

    // Pokemons Ennemies
    for (Pokemon* pokemon :
         enemyTeam->getPokemons())
    {
        if (pokemon == nullptr)
        {
            continue;
        }

        std::string path =
            "../data/images/pokemons/" +
            std::to_string(pokemon->getId()) +
            ".png";

        sf::Sprite sprite =
            loadSpriteFromFile(
                path,
                enemyTextures
            );

        if (enemyTextures.empty())
        {
            continue;
        }

        float maxSize = static_cast<float>(
            std::max(
                enemyTextures.back().getSize().x,
                enemyTextures.back().getSize().y
            )
        );

        float scale = 70.0f / maxSize;

        sprite.setScale(
            scale,
            scale
        );

        float x =
            window.getSize().x - 130.0f;

        float y =
            150.0f +
            enemySprites.size() * 90.0f;

        sprite.setPosition(x, y);

        enemySprites.push_back(sprite);
    }
}

void ArenaScreen::updateCurrentPokemonSprites()
{
    currentPlayerSprite.setColor(sf::Color::Transparent);
    currentEnemySprite.setColor(sf::Color::Transparent);

    if (playerTeam == nullptr || enemyTeam == nullptr)
    {
        return;
    }

    const std::vector<Pokemon*> playerPokemons = playerTeam->getPokemons();
    const std::vector<Pokemon*> enemyPokemons = enemyTeam->getPokemons();

    if (playerPokemonIndex >= 0 &&
        playerPokemonIndex < static_cast<int>(playerPokemons.size()) &&
        playerPokemons[playerPokemonIndex] != nullptr)
    {
        currentPlayerNameText.setString(
            playerPokemons[playerPokemonIndex]->getName()
        );
    }

    if (enemyPokemonIndex >= 0 &&
        enemyPokemonIndex < static_cast<int>(enemyPokemons.size()) &&
        enemyPokemons[enemyPokemonIndex] != nullptr)
    {
        currentEnemyNameText.setString(
            enemyPokemons[enemyPokemonIndex]->getName()
        );
    }

    auto loadCurrentSprite = [](
        const std::vector<Pokemon*>& pokemons,
        int index,
        sf::Texture& texture,
        sf::Sprite& sprite,
        float x,
        float y,
        bool flip
    ) {
        if (index < 0 || index >= pokemons.size() || pokemons[index] == nullptr)
        {
            return;
        }

        const std::string path =
            "../data/images/pokemons/" +
            std::to_string(pokemons[index]->getId()) +
            ".png";

        if (!texture.loadFromFile(path))
        {
            std::cerr << "Error loading current Pokemon sprite: "
                      << path << '\n';
            return;
        }

        sprite.setTexture(texture);

        const sf::Vector2u textureSize = texture.getSize();
        const float maxSize = std::max(textureSize.x, textureSize.y);
        const float scale = 180.0f / maxSize;

        sprite.setScale(flip ? -scale : scale, scale);
        sprite.setPosition(flip ? x + textureSize.x * scale : x, y);
        sprite.setColor(sf::Color::White);
    };

    loadCurrentSprite(
        playerPokemons,
        playerPokemonIndex,
        currentPlayerTexture,
        currentPlayerSprite,
        220.0f,
        400.0f,
        false
    );

    loadCurrentSprite(
        enemyPokemons,
        enemyPokemonIndex,
        currentEnemyTexture,
        currentEnemySprite,
        window.getSize().x - 400.0f,
        400.0f,
        true
    );
}

void ArenaScreen::updateHpTexts()
{
    if (playerTeam == nullptr ||
        enemyTeam == nullptr)
    {
        return;
    }

    std::vector<Pokemon*> playerPokemons =
        playerTeam->getPokemons();

    std::vector<Pokemon*> enemyPokemons =
        enemyTeam->getPokemons();

    if (playerPokemonIndex >= playerPokemons.size() ||
        enemyPokemonIndex >= enemyPokemons.size())
    {
        return;
    }

    Pokemon* playerPokemon =
        playerPokemons[playerPokemonIndex];

    Pokemon* enemyPokemon =
        enemyPokemons[enemyPokemonIndex];

    playerHpText.setString(
        "HP: " +
        std::to_string((int)playerPokemon->getHp()) +
        " / " +
        std::to_string((int)playerPokemon->getMaxHp())
    );

    enemyHpText.setString(
        "HP: " +
        std::to_string((int)enemyPokemon->getHp()) +
        " / " +
        std::to_string((int)enemyPokemon->getMaxHp())
    );
}

void ArenaScreen::attack()
{
    std::cout << "attacking..." << std::endl;
    if (playerTeam == nullptr ||
        enemyTeam == nullptr)
    {
        return;
    }

    std::vector<Pokemon*> playerPokemons =
        playerTeam->getPokemons();

    std::vector<Pokemon*> enemyPokemons =
        enemyTeam->getPokemons();

    if (playerPokemonIndex >= playerPokemons.size() ||
        enemyPokemonIndex >= enemyPokemons.size())
    {
        return;
    }

    Pokemon* playerPokemon =
        playerPokemons[playerPokemonIndex];

    Pokemon* enemyPokemon =
        enemyPokemons[enemyPokemonIndex];


    // Attaque Joueur
    int playerAttack =
        playerPokemon->getAttack();

    int enemyDefense =
        enemyPokemon->getDefense();

    int damage =
        playerAttack - enemyDefense / 2;

    if (damage < 1)
    {
        damage = 1;
    }

    int newHp = enemyPokemon->getHp() - damage;

    if (newHp < 0)
    {
        newHp = 0;
    }
    std::cout <<"Enemy Hp" << newHp << std::endl;

    enemyPokemon->setHp(newHp);

    std::cout <<"Enemy Hp" << enemyPokemon->getHp() << std::endl;
    updateHpTexts();

    // Enemy died
    if (enemyPokemon->getHp() <= 0)
    {
        enemyPokemonIndex++;

        // All enemy Pokémon defeated
        if (enemyPokemonIndex >= enemyPokemons.size())
        {
            std::cout << "PLAYER WINS!" << std::endl;

            for (Pokemon* enemyPokemon : enemyTeam->getPokemons())
            {
                if (playerParty->findById(enemyPokemon->getId()) == nullptr)
                {
                    playerParty->add(new Pokemon(*enemyPokemon));
                }
            }

            gameStateMachine->setGameState(
                std::make_unique<ExplorationScreen>(
                    gameStateMachine,
                    window,
                    playerParty
                )
            );

            return;
        }

        updateCurrentPokemonSprites();
        updateHpTexts();
        return;
    }


    // Ennemi Attaque
    int enemyAttack =
        enemyPokemon->getAttack();

    int playerDefense =
        playerPokemon->getDefense();

    int enemyDamage =
        enemyAttack - playerDefense / 2;

    if (enemyDamage < 1)
    {
        enemyDamage = 1;
    }

    newHp =
        playerPokemon->getHp() -
        enemyDamage;

    if (newHp < 0)
    {
        newHp = 0;
    }

    playerPokemon->setHp(newHp);

    updateHpTexts();


    // Pokemon Joueur vaincu
    if (playerPokemon->getHp() <= 0)
    {
        playerPokemonIndex++;

        // Tous les pokemons joueur sont vaincus
        if (playerPokemonIndex >=playerPokemons.size())
        {
            std::cout << "GAME OVER!" << std::endl;
            gameStateMachine->setGameState(std::make_unique<GameOverScreen>(gameStateMachine, window));
        }

        updateCurrentPokemonSprites();
        updateHpTexts();
    }
}

void ArenaScreen::handleClick(sf::Vector2i mousePosition)
{
    if (attackButton.getGlobalBounds()
        .contains(mousePosition.x,mousePosition.y))
    {
        attack();
    }
}

void ArenaScreen::draw()
{
    window.clear();

    // Background
    window.draw(bgSprite);

    // Titles
    window.draw(arenaText);
    window.draw(playerPokemonText);
    window.draw(enemyPokemonText);

    window.draw(currentPlayerSprite);
    window.draw(currentEnemySprite);
    window.draw(currentPlayerNameText);
    window.draw(currentEnemyNameText);

    // Pokemons Joueur
    for (sf::Sprite& sprite :
         playerSprites)
    {
        window.draw(sprite);
    }


    // Pokemons Ennemies
    for (sf::Sprite& sprite :
         enemySprites)
    {
        window.draw(sprite);
    }


    // HP
    window.draw(playerHpText);
    window.draw(enemyHpText);


    // Boutton Attaque
    window.draw(attackButton);
    window.draw(attackText);

    window.display();
}

bool ArenaScreen::run()
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
                handleClick(sf::Mouse::getPosition(window));
                return true;
            }
        }

        draw();
    }

    return false;
}