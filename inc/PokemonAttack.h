#ifndef POKEMON_POKEMONATTACK_H
#define POKEMON_POKEMONATTACK_H

#include "PokemonVector.h"
#include "PokemonParty.h"

class PokemonAttack : public PokemonVector {
public:
    PokemonAttack();

    void add(Pokemon* pokemon);
    void createFromParty(PokemonParty& party);
    void reintegrate(PokemonParty& party);
};

#endif //POKEMON_POKEMONATTACK_H
