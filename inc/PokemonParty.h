#ifndef POKEMON_POKEMONPARTY_H
#define POKEMON_POKEMONPARTY_H
#include "PokemonVector.h"


class PokemonParty : public PokemonVector{
public:
    PokemonParty();
    void add(Pokemon* pokemon);
    Pokemon* extractByName(const std::string& name);
};


#endif //POKEMON_POKEMONPARTY_H
