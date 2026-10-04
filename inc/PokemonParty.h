#ifndef POKEMON_POKEMONPARTY_H
#define POKEMON_POKEMONPARTY_H
#include "PokemonVector.h"


class PokemonParty : public PokemonVector{
public:
    PokemonParty();
    void add(Pokemon* pokemon);
    std::vector<Pokemon*> getPokemons() const;
    Pokemon* extractByName(const std::string& name);
    using PokemonVector::findById;
};


#endif //POKEMON_POKEMONPARTY_H
