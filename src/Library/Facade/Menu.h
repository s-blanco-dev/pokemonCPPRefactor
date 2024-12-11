//
// Created by jwillmore on 12/8/24.
//

#ifndef MENU_H
#define MENU_H
#include "../Contenedores/Pokedex.h"
#include "../Logica/Entrenador.h"


class Menu {
private:
    Pokedex* pokedex;

    static std::string tipoToString(ETipos tipo);

    public:
    Menu();

    std::string mostrarPokedex();
    std::string listarPokemonsEntrenador(const Entrenador& ente);
    std::string menuPokemonAtaque(const Entrenador& ente);
};



#endif //MENU_H
