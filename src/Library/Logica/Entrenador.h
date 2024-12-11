#include <memory>
#include <vector>

#include "Pokemon.h"
#include "../Interfaces/IItem.h"
//
// Created by jwillmore on 12/5/24.
//
#ifndef ENTRENADOR_H
#define ENTRENADOR_H
#include <string>


class Entrenador {
private:
    std::string nombre;
    std::vector<shared_ptr<Pokemon>> pokemons;
    std::shared_ptr<Pokemon> pokemonActivo;
    int contadorEspecial;
    std::vector<IItem*> items;

public:
    Entrenador(string nombre);

    std::string getNombre() const;

    std::vector<shared_ptr<Pokemon>> getPokemons() const;
    std::shared_ptr<Pokemon> getPokemonActivo();
    int getContadorEspecial() const;
    std::vector<IItem*> getItems() const;
    bool puedeUsarEspecial() const;

    void setPokemonActivo(std::shared_ptr<Pokemon> pokemonActivo);
    void setContadorEspecial(int contadorEspecial);

    void agregarItem(IItem* item);
    void removerItem(IItem* item);
    void agregarPokemon(std::shared_ptr<Pokemon> pokemon);
    void removerPokemon(Pokemon& pokemon);
    std::vector<Movimiento> obtenerMovimientosPokemonActivo() const;
};



#endif //ENTRENADOR_H
