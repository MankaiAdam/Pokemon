#include "../inc/PokemonAttack.h"

#include <iostream>

PokemonAttack::PokemonAttack() {
}

void PokemonAttack::add(Pokemon* pokemon) {
    if (pokemons.size() < MAX_POKEMONS) {
        pokemons.push_back(pokemon);
    }
}

void PokemonAttack::createFromParty(PokemonParty& party) {
    while (pokemons.size() < MAX_POKEMONS) {
        std::string Name;
        std::cout << "Enter the Name of a Pokemon to add to your attack team: ";
        std::cin >> Name;

        Pokemon* pokemon = party.extractByName(Name);

        if (pokemon != nullptr) {
            add(pokemon);
        }
        else {
            std::cout << "Pokemon not found." << std::endl;
        }
    }
}

void PokemonAttack::reintegrate(PokemonParty& party) {
    for (int i = 0; i < pokemons.size(); i++) {
        party.add(pokemons[i]);
    }

    pokemons.clear();
}
