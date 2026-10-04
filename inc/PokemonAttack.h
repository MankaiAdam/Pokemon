#ifndef POKEMON_POKEMONATTACK_H
#define POKEMON_POKEMONATTACK_H

#include "PokemonVector.h"
#include "PokemonParty.h"

class PokemonAttack : public PokemonVector {

public:
    PokemonAttack();
    static const int MAX_POKEMONS = 6;
    void add(Pokemon* pokemon);
    std::vector<Pokemon*> getPokemons();
    void createFromParty(PokemonParty& party);
    void reintegrate(PokemonParty& party);
};

#endif //POKEMON_POKEMONATTACK_H
