# Pokémon

**Pokémon** est un jeu développé en **C++** dans lequel le joueur peut gérer ses Pokémon, constituer son équipe et participer à des combats.

Le jeu utilise un Pokédex chargé depuis un fichier CSV et une interface graphique développée avec **SFML**.

## 🎮 Fonctionnalités

- 📖 **Pokédex** : chargement des Pokémon et de leurs caractéristiques depuis un fichier CSV.
- 👥 **Gestion de l'équipe** : création et gestion de la `PokemonParty` du joueur.
- ⚔️ **Équipe de combat** : sélection de jusqu'à 6 Pokémon pour les combats.
- 🥊 **Combats** : attaques basées sur les statistiques d'attaque et de défense des Pokémon.
- 🖥️ **Interface graphique** : interaction avec les Pokémon et gestion de l'équipe à l'aide de SFML.

## 🛠️ Technologies

- C++
- SFML 2.6.2
- CMake

## 📁 Structure

```text
Pokemon/
├── data/
│   ├── Images
│   ├── fonts
│   └── pokedex.csv
├── inc/
│   └── *.h
├── src/
│   ├── *.cpp
│   └── main.cpp
├── CMakeLists.txt
```

## 🔄 Diagramme des états

```mermaid
stateDiagram-v2
    Ecran_d'accueil

    Ecran_d'accueil --> Exploration : Appui sur une touche

    Exploration --> Rencouter_pokemon : Rencontre aléatoire
    Exploration --> Selection : Rencontre aléatoire

    Rencouter_pokemon --> Exploration : Capture / Fuite

    Selection --> Combat_Arene : Équipe confirmée

    Combat_Arene --> Exploration : Victoire : Vol Pokemon
    
    Combat_Arene --> Game_Over : Echec
   ```

## 📊 Diagramme de classes

```mermaid
classDiagram

    class Pokemon {
        -int id
        -string name
        -string type1
        -string type2
        -double max_hp
        -double hp
        -double attack
        -double defense
        -int evolution
        +getId() int
        +getName() string
        +getType1() string
        +getType2() string
        +getMaxHp() double
        +getHp() double
        +setHp(double) void
        +getAttack() double
        +getDefense() double
        +getEvolution() int
        +sustainDamage(double) void
        +attackPokemon(Pokemon&) void
    }

    class PokemonVector {
        #vector~Pokemon*~ pokemons
        #findById(int) Pokemon*
        #findByName(string) Pokemon*
        +getSize() int
    }

    class Pokedex {
        -Pokedex* instance
        +getInstance() Pokedex&
        +clonePokemon(int) Pokemon*
        +clonePokemon(string) Pokemon*
    }

    class PokemonParty {
        +add(Pokemon*) void
        +getPokemons() vector~Pokemon*~
        +extractByName(string) Pokemon*
        +findByName(string) Pokemon*
    }

    class PokemonAttack {
        +add(Pokemon*) void
        +getPokemons() vector~Pokemon*~
        +createFromParty(PokemonParty&) void
        +reintegrate(PokemonParty&) void
    }

    PokemonVector <|-- PokemonParty
    PokemonVector <|-- PokemonAttack

    Pokedex --> Pokemon : crée des clones
    PokemonVector o-- Pokemon : contient
    PokemonParty --> Pokemon : gère
    PokemonAttack --> Pokemon : utilise
```

## 🚀 Installation

Cloner le projet :

```bash
git clone https://github.com/MankaiAdam/Pokemon.git
cd Pokemon
```

Ouvrir ensuite le projet avec **CLion** et laisser CMake configurer et compiler le projet.


Dans la configuration d'exécution de CLion, définir le **Working Directory** sur le dossier `src` :

```text
$ProjectFileDir$/src
```


Le fichier `data/pokedex.csv` doit être présent pour permettre le chargement du Pokédex.

## 👨‍💻 Auteur

**Adam Mankai**
