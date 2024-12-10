#include <memory>
#include <vector>

#include "Pokemon.h"
#include "../Interfaces/IItem.h"
//
// Created by jwillmore on 12/5/24.
//
using namespace std;

#ifndef ENTRENADOR_H
#define ENTRENADOR_H
#include <string>


class Entrenador {
private:
    string nombre;
    vector<Pokemon> pokemons;
    Pokemon pokemonActivo;
    int contadorEspecial;
    vector<IItem*> items;

public:
    Entrenador(string nombre);

    string getNombre() const;
    vector<Pokemon> getPokemons() const;
    Pokemon& getPokemonActivo();
    int getContadorEspecial() const;
    vector<IItem*> getItems() const;
    bool puedeUsarEspecial() const;

    void setPokemonActivo(Pokemon& pokemonActivo);
    void setContadorEspecial(int contadorEspecial);

    void agregarItem(IItem* item);
    void removerItem(IItem* item);
    void agregarPokemon(const Pokemon& pokemon);
    void removerPokemon(Pokemon& pokemon);
};



#endif //ENTRENADOR_H
