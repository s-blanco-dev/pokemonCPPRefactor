//
// Created by jwillmore on 12/8/24.
//

#include "Facade.h"
#include <format>
#include <stdexcept>
#include <string>
#include <vector>

// Bitácora del 9/12/2024:
// Fui diagnosticado con esquizofrenia paranoide
// Los punteros inteligentes me siguien hasta en el supermercado
// no veo la luz desde hace 2 semanas

// CONSTRUCTOR, DESTRUCTOR, SINGLETON
// -------------------------
Facade *Facade::instance = nullptr;

Facade::Facade() {
  this->pokedexActual = Pokedex::getInstance();
  this->batallaActual = nullptr;
  this->listaEspera = vector<Entrenador>();
  this->menuActual = new Menu();
}

Facade *Facade::getInstance() {
  if (instance == nullptr) {
    instance = new Facade();
  }
  return instance;
}

void Facade::resetInstance() {
  Pokedex::resetInstance();
  delete instance;    // Liberar la instancia existente
  instance = nullptr; // Evitar apuntar a memoria inválida
}

Facade::~Facade() {
  delete this->batallaActual;
  delete this->menuActual; // Liberar memoria asignada dinámicamente
}

// METODOS PUBLICOS
// -------------------------
std::string Facade::unirBatalla(std::string nombreEnt) {
  listaEspera.push_back(Entrenador(nombreEnt));

  return format("**{}** está esperando para batallar :crossed_swords:\n",
                nombreEnt);
}

std::string Facade::iniciarBatalla(IGenerador *gen) {
  try {
    if (listaEspera.size() < 2) {
      throw invalid_argument("Debe haber al menos dos entrenadores para "
                             "empezar una batalla:exclamation:");
    }

    auto ent1 = std::make_shared<Entrenador>(Entrenador(listaEspera[0]));
    auto ent2 = std::make_shared<Entrenador>(Entrenador(listaEspera[1]));

    batallaActual = new Batalla(ent1, ent2, gen);
    return batallaActual->iniciarBatalla();
  } catch (std::exception &e) {
    return e.what();
  }
}

std::string Facade::mostrarPokedex() {
  try {
    if (pokedexActual->getPokemons().size() == 0) {
      throw invalid_argument("La Pokedex está vacía:exclamation:");
    }
    return menuActual->mostrarPokedex();
  } catch (std::exception &e) {
    return e.what();
  }
}

std::string Facade::seleccionarPokemon(std::string nombrePok,
                                       std::string nombreEnt) {
  try {
    if (!existeBatalla()) {
      throw invalid_argument(
          ":prohibited:**No hay batalla en curso**:prohibited:");
    }

    auto ente = batallaActual->obtenerEntrenadorPorNombre(nombreEnt);
    Pokemon *pokemon = pokedexActual->getPokemonByName(nombrePok);

    if (pokemon == nullptr) {
      throw invalid_argument("El pokemon no está disponible");
    }

    // Pasar punteros directamente a Batalla
    return batallaActual->seleccionarPokemon(ente, *pokemon);
  } catch (std::exception &e) {
    return e.what();
  }
}

std::string Facade::desplegarMenuAtaque(std::string nombreEnt) {
  try {

    if (!existeBatalla()) {
      throw invalid_argument(
          ":prohibited:**No hay batalla en curso**:prohibited:");
    }

    auto ente = batallaActual->obtenerEntrenadorPorNombre(nombreEnt);

    if (ente->getPokemonActivo() == nullptr) {
      throw std::invalid_argument(
          format("No tienes ningún pokemon activo, {}:exclamation:",
                 ente->getNombre()));
    }

    if (ente->getPokemonActivo()->isDebil()) {
      throw std::invalid_argument(
          format(":prohibited: {} está debilitado :prohibited:",
                 ente->getPokemonActivo()->getNombre()));
    }

    if (!batallaActual->esTurnoDe(*ente)) {
      throw std::invalid_argument(
          format("No es tu turno, {}:exclamation:", nombreEnt));
    }

    return menuActual->menuPokemonAtaque(*ente);
  } catch (std::exception &e) {
    return e.what();
  }
}

// Bitácora del 11/12/2024
// Las alucinaciones no dan tregüa
// luego de 3 días de debugging, logré hacer funcionar el metodo atacar
// Nota: NO USAR REFERENCIAS Y PUNTEROS CRUDOS. EN LO POSIBLE USAR SHARED_PTR
std::string Facade::atacar(std::string nombreEnt, std::string nombreMov) {
  try {

    if (!existeBatalla()) {
      throw invalid_argument(
          ":prohibited:**No hay batalla en curso**:prohibited:");
    }

    auto ente = batallaActual->obtenerEntrenadorPorNombre(nombreEnt);

    if (ente->getPokemonActivo() == nullptr) {
      throw std::invalid_argument(
          format("No tienes ningún pokemon activo, {}:exclamation:",
                 ente->getNombre()));
    }

    auto ataque = buscarMovimientoPorNombre(nombreMov, *ente);
    if (ataque == nullptr) {
      throw std::invalid_argument("Movimiento no encontrado!");
    }

    return batallaActual->atacar(ente, *ataque);
  } catch (std::exception &e) {
    return e.what();
  }
}

// METODOS PRIVADOS
// -------------------------

bool Facade::existeBatalla() {
  if (batallaActual == nullptr) {
    return false;
  }
  return true;
}

Entrenador *Facade::buscarEntrenadorPorNombre(std::string nombre) {
  for (Entrenador &ent : this->listaEspera) {
    if (nombre == ent.getNombre()) {
      return &ent;
    }
  }
  return nullptr;
}

Movimiento *Facade::buscarMovimientoPorNombre(std::string nombre,
                                              Entrenador ente) {
  std::vector<Movimiento> &movs =
      ente.obtenerMovimientosPokemonActivo(); // ME HABÍA OLVIDADO DE PONER EL
                                              // OPERADOR DE REFERENCIACIÓN (&)
  for (auto &mov : movs) {
    if (nombre == mov.getNombre())
      return &mov;
  }
  return nullptr;
}
