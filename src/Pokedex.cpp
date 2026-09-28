#include "Pokedex.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Pokedex* Pokedex::instance = nullptr;

static std::string fileName = "../data/pokedex.csv";

Pokedex::Pokedex() {
    std::cout << "*** Constructeur du Pokedex ***" << std::endl;

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "File " << fileName << " not found" << std::endl;
        return;
    }

    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream inputstringstream(line);

        std::string cell;
        std::vector<std::string> lineData;

        while (std::getline(inputstringstream, cell, ',')) {
            lineData.push_back(cell);
        }

        int id = std::stoi(lineData.at(0));
        std::string name = lineData.at(1);

        std::string type1 = lineData.at(2);
        std::string type2 = lineData.at(3);
        double maxHp = std::stod(lineData.at(5));
        double hp = maxHp;

        double attackValue = std::stod(lineData.at(6));
        double defenseValue = std::stod(lineData.at(7));

        int evolution = std::stoi(lineData.at(11));

        pokemons.push_back(
            new Pokemon(
                id,
                name,
                type1,
                type2,
                maxHp,
                hp,
                attackValue,
                defenseValue,
                evolution
            )
        );
    }
}

Pokedex& Pokedex::getInstance() {
    if (instance == nullptr) {
        instance = new Pokedex();
    }

    return *instance;
}

Pokemon* Pokedex::clonePokemon(const std::string& name) const {
    Pokemon* found = findByName(name);
    if (found == nullptr)
        throw std::out_of_range("Pokemon not found");

    return new Pokemon(*found);
}
Pokemon* Pokedex::clonePokemon(const int id) const {
    Pokemon* found = findById(id);
    if (found == nullptr)
        throw std::out_of_range("Pokemon not found");

    return new Pokemon(*found);
}