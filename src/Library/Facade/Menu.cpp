#include "Menu.h"
#include "../Enums/EnumTools.h"
#include <format>

// CONSTRUCTOR
// -------------------------
Menu::Menu() { this->pokedex = Pokedex::getInstance(); }

// METODOS PUBLICOS
// -------------------------
std::string Menu::mostrarPokedex() {
  std::string mensaje;
  const std::vector<Pokemon> &listaPokemons = pokedex->getPokemons();

  for (auto pok : listaPokemons) {
    int pokemonHPMax = pok.getHPMax();
    std::string tiPokemon = EnumTools::tipoToString(pok.getTipo());

    mensaje += std::format("- **{}** | :heart: {} **HP Max**| :label: **{}**\n",
                           pok.getNombre(), pokemonHPMax, tiPokemon);
  }
  return mensaje;
}

std::string Menu::menuPokemonAtaque(Entrenador &entrenador) {
  std::string mensaje;

  // Obtener el Pokémon activo
  std::shared_ptr<Pokemon> pokemonActivo = entrenador.getPokemonActivo();

  // Información de salud del Pokémon activo
  int pokemonHP = pokemonActivo->getHP();
  int pokemonHPMax = pokemonActivo->getHPMax();

  // Estado del Pokémon activo
  std::string estadoPokemon =
      EnumTools::estadoToString(pokemonActivo->getEstado());

  // Construir encabezado del menú
  mensaje += format(":smirk_cat: **{}**: :heart: [{}/{}] HP | :pill: **{}**\n",
                    pokemonActivo->getNombre(), pokemonHP, pokemonHPMax,
                    estadoPokemon);

  // Obtener movimientos del Pokémon activo
  vector<Movimiento> movimientosActivos = pokemonActivo->getMovimientos();

  // Agregar cada movimiento al menú
  for (size_t i = 0; i < movimientosActivos.size(); ++i) {
    Movimiento &movimiento = movimientosActivos[i];

    std::string tipoMovimiento = EnumTools::tipoToString(movimiento.getTipo());
    int currentPP = movimiento.getCurrentPP();
    int maxPP = movimiento.getPP();

    if (movimiento.esEspecial()) {
      mensaje += format(
          "{}. **{}** :sparkles: | :label: **{}** | :boomerang: [{}/{}]\n",
          i + 1, movimiento.getNombre(), tipoMovimiento, currentPP, maxPP);
    } else {
      mensaje +=
          format("{}. {} | :label: **{}** | :boomerang: [{}/{}]\n", i + 1,
                 movimiento.getNombre(), tipoMovimiento, currentPP, maxPP);
    }
  }

  return mensaje;
}

// METODOS PRIVADOS
// -------------------------

// tipoToString y estadoToString fueron movidos a EnumTools -> todavía no me
// convence
