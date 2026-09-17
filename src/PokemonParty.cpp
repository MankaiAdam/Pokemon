//
// Created by Adam Mankai on 9/14/2026.
//

#include "PokemonParty.h"

PokemonParty::PokemonParty() {

}
void PokemonParty::add(Pokemon* pokemon) {
    this->pokemons.push_back(pokemon);
}

Pokemon* PokemonParty::extractByName(const std::string& name) {
    for (int i = 0; i < pokemons.size(); i++) {
        if (pokemons[i]->getName() == name) {
            Pokemon* pokemon = pokemons[i];
            pokemons.erase(pokemons.begin() + i);
            return pokemon;
        }
    }

    return nullptr;
}