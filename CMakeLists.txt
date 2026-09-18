cmake_minimum_required(VERSION 3.21)

project(Pokemon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Pokemon src/main.cpp
        src/Pokemon.cpp
        inc/Pokemon.h
        src/PokemonVector.cpp
        inc/PokemonVector.h
        src/Pokedex.cpp
        inc/Pokedex.h
        src/PokemonParty.cpp
        inc/PokemonParty.h
        src/PokemonAttack.cpp
        inc/PokemonAttack.h
        src/SelectionScreen.h
        inc/SelectionScreen.cpp)

find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

include_directories(inc)

target_link_libraries(Pokemon PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)