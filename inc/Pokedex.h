#ifndef POKEDEX_H
#define POKEDEX_H

#include "PokemonVector.h"
#include <string>

class Pokedex : public PokemonVector {
private:
    static Pokedex* instance;

    Pokedex();
public:
    Pokedex(const Pokedex&) = delete;
    Pokedex& operator=(const Pokedex&) = delete;

    static Pokedex& getInstance();

    Pokemon* clonePokemon(const std::string &name) const;
    Pokemon* clonePokemon(int id) const;
};

#endif // POKEDEX_H