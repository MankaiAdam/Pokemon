//
// Created by Adam Mankai on 9/10/2026.
//

#ifndef UNTITLED_POKEMON_H
#define UNTITLED_POKEMON_H
#include <string>


class Pokemon {
private:
    int id;
    std::string name;
    double max_hp;
    double hp;
    double attack;
    double defense;
    int evolution;

public:
    Pokemon() = delete;
    Pokemon(int id, const std::string &name,double max_hp, double hp, double attack, double defense, int evolution);
    Pokemon(const Pokemon &anotherPokemon);
    ~Pokemon();

    int getId() const;

    std::string getName() const;

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
