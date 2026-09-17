#include "Pokemon.h"

#include <iostream>

Pokemon::Pokemon(const int id, const std::string &name,const double max_hp, const double hp, const double attack, const double defense, const int evolution):
id(id),name(name),max_hp(max_hp),hp(hp),attack(attack),defense(defense),evolution(evolution) {
}
Pokemon::Pokemon(const Pokemon &anotherPokemon):
id(anotherPokemon.id),name(anotherPokemon.name),max_hp(anotherPokemon.max_hp),hp(anotherPokemon.hp),attack(anotherPokemon.attack),defense(anotherPokemon.defense),evolution(anotherPokemon.evolution){
}
Pokemon::~Pokemon() {
    std::cout << "Pokemon detruit" << std::endl;
}

int Pokemon::getId() const {
    return id;
}

std::string Pokemon::getName() const {
    return name;
}

double Pokemon::getMaxHp() const {
    return max_hp;
}

double Pokemon::getHp() const {
    return hp;
}

void Pokemon::sustainDamage(const double value) {
    hp = std::max(hp - value,0.0);
    if (hp <= 0) std::cout<<name<<" est decede"<<std::endl;
}

double Pokemon::getAttack() const {
    return attack;
}

double Pokemon::getDefense() const {
    return defense;
}

int Pokemon::getEvolution() const {
    return evolution;
}

void Pokemon::displayInfo() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Hitpoint: " << hp << std::endl;
    std::cout << "Attack: " <<attack << std::endl;
    std::cout << "Defense: " << defense << std::endl;
    std::cout << "Evolution: " << evolution << std::endl;
}

void Pokemon::attackPokemon(Pokemon& other) const {
    double diff = attack - other.getDefense();
    other.sustainDamage(std::max(diff,0.0));
}
