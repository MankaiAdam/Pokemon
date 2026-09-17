#ifndef POKEMONVECTOR_H
#define POKEMONVECTOR_H

#include <vector>
#include "Pokemon.h"

class PokemonVector {
protected:
    std::vector<Pokemon*> pokemons;
    Pokemon* findByName(const std::string& name) const;
public:
    PokemonVector() = default;
    virtual ~PokemonVector();
    int getSize() const;

};

#endif // POKEMONVECTOR_H