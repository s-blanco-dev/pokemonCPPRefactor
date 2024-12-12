//
// Created by jwillmore on 12/8/24.
//

#include "Menu.h"

#include <format>

// CONSTRUCTOR
// -------------------------
Menu::Menu() {
    this->pokedex = Pokedex::getInstance();
}

// METODOS PUBLICOS
// -------------------------
std::string Menu::mostrarPokedex() {
    std::string mensaje;
    const std::vector<Pokemon>& listaPokemons = pokedex->getPokemons();

    for (auto pok: listaPokemons) {
        int pokemonHPMax = pok.getHPMax();
        std::string tiPokemon = tipoToString(pok.getTipo());

        mensaje += std::format("- **{}** | :heart: {} **HP Max**| :label: **{}**\n", pok.getNombre(),
                         pokemonHPMax,
                         tiPokemon);
    }

    return mensaje;
}

std::string Menu::menuPokemonAtaque(Entrenador& entrenador) {
    std::string mensaje;

    // Obtener el Pokémon activo
    std::shared_ptr<Pokemon> pokemonActivo = entrenador.getPokemonActivo();

    // Información de salud del Pokémon activo
    int pokemonHP = static_cast<int>(pokemonActivo->getHP());
    int pokemonHPMax = static_cast<int>(pokemonActivo->getHPMax());

    // Estado del Pokémon activo
    std::string estadoPokemon = estadoToString(pokemonActivo->getEstado());

    // Construir encabezado del menú
    mensaje += format(":smirk_cat: **{}**: :heart: [{}/{}] HP | :pill: **{}**\n",
                      pokemonActivo->getNombre(), pokemonHP, pokemonHPMax, estadoPokemon);

    // Obtener movimientos del Pokémon activo
    vector<Movimiento> movimientosActivos = pokemonActivo->getMovimientos();

    // Agregar cada movimiento al menú
    for (size_t i = 0; i < movimientosActivos.size(); ++i) {
        Movimiento& movimiento = movimientosActivos[i];

        std::string tipoMovimiento = tipoToString(movimiento.getTipo());
        int currentPP = movimiento.getCurrentPP();
        int maxPP = movimiento.getPP();

        if (movimiento.esEspecial()) {
            mensaje += format("{}. **{}** :sparkles: | :label: **{}** | :boomerang: [{}/{}]\n",
                              i + 1, movimiento.getNombre(), tipoMovimiento, currentPP, maxPP);
        } else {
            mensaje += format("{}. {} | :label: **{}** | :boomerang: [{}/{}]\n",
                              i + 1, movimiento.getNombre(), tipoMovimiento, currentPP, maxPP);
        }
    }

    return mensaje;
}



// METODOS PRIVADOS
// -------------------------

// SOLUCION TEMPORAL !!!!!
std::string Menu::tipoToString(ETipos tipo) {
    switch (tipo) {
        case ETipos::FUEGO: return "Fuego";
        case ETipos::PLANTA: return "Planta";
        case ETipos::AGUA: return "Agua";
        case ETipos::PSIQUICO: return "Psiquo";
        case ETipos::ELECTRICO: return "Electrico";
        case ETipos::BICHO: return "Bicho";
        case ETipos::HADA: return "Hada";\
        case ETipos::VENENO: return "Veneno";
        case ETipos::NORMAL: return "Normal";
        case ETipos::ROCA: return "Roca";
        case ETipos::TIERRA: return "Tierra";
        case ETipos::HIELO: return "Hilo";
        case ETipos::SINIESTRO: return "Sinistro";
        case ETipos::FANTASMA: return "Fantasma";
        case ETipos::LUCHA: return "Lucha";
        case ETipos::DRAGON: return "Dragon";
        case ETipos::ACERO: return "Acero";
        case ETipos::VOLADOR: return "Volador";
        default: return "Desconocido";
    }
}

std::string Menu::estadoToString(EEstado estado) {
     switch (estado) {
         case EEstado::NORMAL: return "Normal";
         case EEstado::DORMIDO: return "Dormido";
         case EEstado::QUEMADO: return "Quemado";
         case EEstado::ENVENENADO: return "Envenado";
         case EEstado::PARALIZADO: return "Paralizado";
        default: return "Desconocido";
    }
}