//
// Created by Adam Mankai on 9/10/2026.
//

#ifndef UNTITLED_POKEMON_H
#define UNTITLED_POKEMON_H
#include <string>
#include <vector>


class Pokemon {
private:
    int id;
    std::string name;
    std::string type1;
    std::string type2;
    double max_hp;
    double hp;
    double attack;
    double defense;
    int evolution;

public:
    static const std::vector<std::string> POKEMONS_TYPES;

    Pokemon() = delete;
    Pokemon(int id, const std::string &name, const std::string &type1, const std::string &type2,double max_hp, double hp, double attack, double defense, int evolution);
    Pokemon(const Pokemon &anotherPokemon);
    ~Pokemon();

    int getId() const;

    std::string getName() const;

    std::string getType1() const;

    std::string getType2() const;

    double getMaxHp() const;

    double getHp() const;

    void sustainDamage(double value);

    double getAttack() const;

    double getDefense() const;

    int getEvolution() const;

    void displayInfo() const;

    void attackPokemon(Pokemon& other) const;
};


#endif //UNTITLED_POKEMON_H
