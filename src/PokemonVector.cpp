#include "../inc/PokemonVector.h"

PokemonVector::~PokemonVector() {
    for (Pokemon* pokemon : pokemons) {
        delete pokemon;
    }
}

Pokemon* PokemonVector::findByName(const std::string& name) const {
    for (Pokemon* pokemon : pokemons) {
        if (pokemon->getName() == name) {
            return pokemon;
        }
    }

    return nullptr;
}

int PokemonVector::getSize() const {
    return pokemons.size();
}