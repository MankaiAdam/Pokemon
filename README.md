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
│   └── pokedex.csv
├── inc/
│   ├── Pokemon.h
│   ├── PokemonVector.h
│   ├── Pokedex.h
│   ├── PokemonParty.h
│   └── PokemonAttack.h
├── src/
│   ├── Pokemon.cpp
│   ├── PokemonVector.cpp
│   ├── Pokedex.cpp
│   ├── PokemonParty.cpp
│   └── PokemonAttack.cpp
├── main.cpp
├── CMakeLists.txt
└── vcpkg.json
```

## 🚀 Installation

Cloner le projet :

```bash
git clone https://github.com/MankaiAdam/Pokemon.git
cd Pokemon
```

Ouvrir ensuite le projet avec **CLion** et laisser CMake configurer et compiler le projet.

Le fichier `data/pokedex.csv` doit être présent pour permettre le chargement du Pokédex.

## 👨‍💻 Auteur

**Adam Mankai**