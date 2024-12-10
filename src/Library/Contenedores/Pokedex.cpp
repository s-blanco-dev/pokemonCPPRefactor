//
// Created by jwillmore on 12/6/24.
//

#include "Pokedex.h"

#include <algorithm>

#include "../Pokemons/Charizard.h"
#include "../Pokemons/Pikachu.h"
#include <vector>

Pokedex* Pokedex::instance = nullptr;

// CONSTRUCTOR PRIVADO
Pokedex::Pokedex() {
    this->pokemons.push_back(Pikachu());
    this->pokemons.push_back(Charizard());
    // AGREGAR RESTANTES
}


// APLICO SINGLETON
Pokedex* Pokedex::getInstance() {
    if (instance == nullptr) {
        instance = new Pokedex();
    }
    return instance;
}

// DESTRUCTOR
Pokedex::~Pokedex() {
    // Libera la memoria de los Pokémon creados dinámicamente
    for (Pokemon pokemon : pokemons) {
        delete &pokemon;
    }
}

void Pokedex::addPokemon(Pokemon& pokemon) {
    this->pokemons.push_back(pokemon);
}

void Pokedex::removePokemon(const Pokemon& pokemon) {
    for (auto it = pokemons.begin(); it != pokemons.end(); ++it) {
        if (it->getNombre() == pokemon.getNombre()) {
            pokemons.erase(it);
            break; // Salimos después de eliminar
        }
    }
}

vector<Pokemon> Pokedex::getPokemons() const{
  return this->pokemons;
}

Pokemon* Pokedex::getPokemonByName(const std::string& nombre) {
    for (auto& pokemon : pokemons) {
        if (pokemon.getNombre() == nombre) {
            return &pokemon; // Retorna un puntero al Pokémon encontrado
        }
    }
    return nullptr;
}

