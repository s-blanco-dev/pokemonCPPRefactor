//
// Created by jwillmore on 12/6/24.
//

#ifndef POKEDEX_H
#define POKEDEX_H
#include <vector>

#include "../Logica/Pokemon.h"

class Pokedex {
protected:
  std::vector<Pokemon> pokemons;
  static Pokedex *instance;

  Pokedex();

public:
  static Pokedex *getInstance();
  static void resetInstance();

  void addPokemon(Pokemon &pokemon);
  void removePokemon(const Pokemon &pokemon);
  std::vector<Pokemon> getPokemons() const;

  Pokemon *getPokemonByName(const std::string &nombre);
};
#endif // POKEDEX_H
