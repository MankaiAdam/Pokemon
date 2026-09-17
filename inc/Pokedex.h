#ifndef POKEDEX_H
#define POKEDEX_H

#include "PokemonVector.h"
#include <string>

class Pokedex : public PokemonVector {
private:
    static Pokedex* instance;

    Pokedex();
public:
    static Pokedex& getInstance();

    Pokemon cloneByName(const std::string &name) const;
};

#endif // POKEDEX_H