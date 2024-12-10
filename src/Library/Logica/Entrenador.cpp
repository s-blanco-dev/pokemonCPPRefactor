//
// Created by jwillmore on 12/5/24.
//

#include "Entrenador.h"

#include <bits/streambuf_iterator.h>

#include "../Items/SuperPocion.h"

// CONSTRUCTOR
// -------------------------
Entrenador::Entrenador(string nombre) {
    this->nombre = nombre;
    this->items = {new SuperPocion()};
}


// GETTERS
// -------------------------
string Entrenador::getNombre() const {
    return nombre;
}

vector<Pokemon> Entrenador::getPokemons() const {
    return pokemons;
}

Pokemon& Entrenador::getPokemonActivo(){
    return pokemonActivo;
}

int Entrenador::getContadorEspecial() const {
    return contadorEspecial;
}

vector<IItem*> Entrenador::getItems() const {
    return items;
}

void Entrenador::setPokemonActivo(Pokemon& pokemon) {
    this->pokemonActivo = pokemon;
}

void Entrenador::setContadorEspecial(int contador) {
    contadorEspecial = contador;
}

// METODOS PUBLICOS
// -------------------------
bool Entrenador::puedeUsarEspecial() const {
    if (contadorEspecial == 0) return true;
    return false;
}

void Entrenador::agregarPokemon(const Pokemon &pokemon) {
    pokemons.push_back(pokemon);
}

void Entrenador::removerPokemon(Pokemon &pokemon) {
    for (int i = 0; i < pokemons.size(); i++) {
        if (pokemon.getNombre() == pokemons[i].getNombre()) {
            pokemons.erase(pokemons.begin() + i);
        }
    }
}

void Entrenador::agregarItem(IItem *item) {
    items.push_back(item);
}

void Entrenador::removerItem(IItem *item) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i] == item) {
            items.erase(items.begin() + i);
        }
    }
}








