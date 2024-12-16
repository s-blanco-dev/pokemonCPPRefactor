//
// Created by jwillmore on 12/6/24.
//

#include "Batalla.h"
#include "../Contenedores/Pokedex.h"
#include "../Enums/EnumTools.h"
#include "../Generador/GeneradorContexto.h"
#include "../Generador/IGenerador.h"
#include "LogicaAtaque.h"
#include "Movimiento.h"
#include "Pokemon.h"
#include <cstdlib>
#include <exception>
#include <format>
#include <memory>
#include <stdexcept>
#include <string>

// GETTERS Y SETTERS
// -------------------------
// void Batalla::setEntrenadorActual(Entrenador &ent){
//   this->entrenadorActual = ent;
// }

Entrenador Batalla::getEntrenadorActual() const { return *entrenadorActual; }

// CONSTRUCTOR
// -------------------------
Batalla::Batalla(std::shared_ptr<Entrenador> ent1,
                 std::shared_ptr<Entrenador> ent2, IGenerador *gen)
    : entrenador_1(ent1), entrenador_2(ent2),
      entrenadorActual(
          ent1), // Por defecto inicializo el entrenador1 como actual
      pokedex(Pokedex::getInstance()), contadorTurno(0),
      generador(GeneradorContexto(gen)), _logica(LogicaAtaque(gen)) {}

// METODOS PUBLICOS
// -------------------------
std::string Batalla::iniciarBatalla() {
  if (generador.generar(2) == 0) {
    entrenadorActual = entrenador_2;
  } else {
    entrenadorActual = entrenador_1;
  }

  return format("Atención **{}** y **{}**, ha empezado la batalla! :trumpet: "
                "\nEs turno de **{}**",
                entrenador_1->getNombre(), entrenador_2->getNombre(),
                entrenadorActual->getNombre());
}

// 3 días para hacer funcionar lo más básico del metodo atacar -> mi familia me
// reservó un cuarto en el Vilardebó
std::string Batalla::atacar(std::shared_ptr<Entrenador> &atacante,
                            Movimiento &ataque) {
  try {
    std::string mensaje;
    verificarTurno(atacante); // verifica que sea el turno del entrenador

    auto defensor = obtenerDefensor(atacante); // obtiene el entrenador defensor
    auto pokemonAtacante = atacante->getPokemonActivo();
    auto pokemonDefensor = defensor->getPokemonActivo();

    verificarCondicionesPokemonActivo(atacante);
    verificarCondicionesPokemonActivo(defensor);

    verificarCondicionesAtaque(atacante, ataque);
    verificarEstadosPokemon(pokemonAtacante);

    // Aplica el ataque
    mensaje += _logica.aplicarAtaque(atacante, defensor, ataque);

    if (finBatalla()) {
      mensaje +=
          format("**{} ha ganado la batalla**:tada:\n", atacante->getNombre());
    }

    ataque.setCurrentPP(
        ataque.getPP() -
        1); // Reduce en 1 el contador de usos disponibles para el ataque
    siguienteTurno();

    return mensaje;
  } catch (const std::exception &e) {
    return e.what();
  }
}

// Bitácora del 10/12/2024:
// Primer intento de suicidio
// Hace 4 días que no puedo solucionar el bug
// Se selecciona Pikachu pero mágicamente se convierte en Charizard
// PD: lo solucioné, nuevamente los punteros y referencias me generaron un
// aneurisma

std::string Batalla::seleccionarPokemon(const std::shared_ptr<Entrenador> &ente,
                                        Pokemon &pok) {
  try {
    auto copiaPokemon = std::make_shared<Pokemon>(pok);

    verificarTurno(ente);

    ente->agregarPokemon(copiaPokemon);   // Usar la copia
    pokedex->removePokemon(pok);          // Eliminar el original de la Pokédex
    ente->setPokemonActivo(copiaPokemon); // Usar la copia como activo
    siguienteTurno();

    return format(
        "**{}** ha seleccionado a **{}** para su equipo :inbox_tray:\n",
        ente->getNombre(), copiaPokemon->getNombre());

    // FINALMENTE FUNCIONA -> (3 días programando en C++ derivaron en 7 años de
    // estancia en el Vilardebó)
  } catch (std::exception &e) {
    return e.what();
  }
}

std::shared_ptr<Entrenador>
Batalla::obtenerEntrenadorPorNombre(std::string nombre) {
  if (nombre == entrenador_1->getNombre()) {
    return entrenador_1;
  }
  return entrenador_2;
}

bool Batalla::esTurnoDe(const Entrenador &entrenador) {
  return (entrenador.getNombre() == entrenadorActual->getNombre());
}

// METODOS PRIVADOS
// -------------------------

bool Batalla::finBatalla() {
  return (entrenador_1->todosPokemonDebiles() ||
          entrenador_2->todosPokemonDebiles());
}

void Batalla::siguienteTurno() {
  this->contadorTurno++;
  this->entrenadorActual =
      (entrenadorActual->getNombre() == entrenador_1->getNombre())
          ? entrenador_2
          : entrenador_1;
}

// Auxiliares de atacar()
//---

void Batalla::verificarTurno(const std::shared_ptr<Entrenador> &atacante) {
  if (!esTurnoDe(*atacante)) {
    throw std::invalid_argument(
        format("No es tu turno, {}!", atacante->getNombre()));
  } // verifica que sea el turno del entrenador
}

void Batalla::verificarCondicionesPokemonActivo(
    const std::shared_ptr<Entrenador> &entrenador) {
  if (entrenador->getPokemonActivo() == nullptr) {
    throw std::invalid_argument(format("No tienes ningún pokemon activo, {}!",
                                       entrenador->getNombre()));
  }

  if (entrenador->getPokemonActivo()->isDebil()) {
    throw std::invalid_argument(
        format(":prohibited: {} está debilitado :prohibited:",
               entrenador->getPokemonActivo()->getNombre()));
  } // No ataca si el pokemon está debil
};

std::shared_ptr<Entrenador>
Batalla::obtenerDefensor(const std::shared_ptr<Entrenador> &atacante) const {
  return (atacante->getNombre() == entrenador_1->getNombre()) ? entrenador_2
                                                              : entrenador_1;
}

void Batalla::verificarCondicionesAtaque(
    const std::shared_ptr<Entrenador> &atacante, Movimiento &ataque) const {
  if (ataque.esEspecial() && atacante->getContadorEspecial() != 0) {
    throw invalid_argument(
        format(":prohibited: Debes esperar **{}** turnos más para usar un "
               "ataque especial :prohibited:",
               atacante->getContadorEspecial()));
  } // verifica que pueda usar ataque especial

  if (ataque.getCurrentPP() == 0) {
    throw invalid_argument(
        format("**{}** está agotado:exclamation:", ataque.getNombre()));
  } // verifica que tenga ataques disponibles
}

void Batalla::verificarEstadosPokemon(std::shared_ptr<Pokemon> &pokemon) {
  EEstado estadoPokemonAtacante = _logica.verificarEstadoPokemon(pokemon);

  if (estadoPokemonAtacante == EEstado::DORMIDO ||
      estadoPokemonAtacante == EEstado::PARALIZADO) {
    siguienteTurno();
    throw std::invalid_argument(format(
        "{} está **{}** y no puede atacar :prohibited:\n", pokemon->getNombre(),
        EnumTools::estadoToString(estadoPokemonAtacante)));
  }
}
