//
// Created by jwillmore on 12/7/24.
//

#include "LogicaAtaque.h"
#include "../Contenedores/Efectividad.h"
#include "../Enums/EnumTools.h"
#include "../Generador/GeneradorContexto.h"
#include "../Generador/IGenerador.h"
#include "Movimiento.h"
#include "Pokemon.h"
#include <format>
#include <memory>
#include <string>

// CONSTRUCTOR
// -------------------------
LogicaAtaque::LogicaAtaque(IGenerador *gen) : generador(gen) {}

// METODOS PUBLICOS
// -------------------------
std::string
LogicaAtaque::aplicarAtaque(std::shared_ptr<Entrenador> &atacante,
                            const std::shared_ptr<Entrenador> &defensor,
                            const Movimiento &ataque) {
  auto pokemonAtaque = atacante->getPokemonActivo();
  auto pokemonDefensa = defensor->getPokemonActivo();

  if (!pokemonAtaque || !pokemonDefensa) {
    throw std::runtime_error("Error: Pokémon activo no válido.");
  }

  int danioBase = calcularDanioBase(pokemonAtaque, pokemonDefensa, ataque);

  std::string mensaje;

  mensaje += format("*{}* ha usado **{}**:exclamation:\n",
                    atacante->getNombre(), ataque.getNombre());

  if (esCritico()) {
    mensaje += "**ATAQUE CRÍTICO**:100:\n";
    danioBase *= 2;
  }

  mensaje += format("**{}** ha recibido {} puntos de daño:exclamation:\n",
                    pokemonDefensa->getNombre(), danioBase);

  // APLICAR EFECTOS
  mensaje += aplicarEfectosEstado(pokemonDefensa, ataque);
  pokemonDefensa->recibirDanio(danioBase);
  actualizarContadores(atacante, ataque);

  // VERIFICAR DEBILIDAD
  if (pokemonDefensa->isDebil()) {
    mensaje += format("**{}** se ha debilitado:rotating_light:\n",
                      pokemonDefensa->getNombre());
  }

  return mensaje;
}

EEstado LogicaAtaque::verificarEstadoPokemon(std::shared_ptr<Pokemon> pok) {
  if (pok->getTurnosDormido() != 0) {
    pok->setTurnosDormido(pok->getTurnosDormido() - 1);
    return EEstado::DORMIDO;
  }
  if (pok->getEstado() == EEstado::PARALIZADO) {
    if (generador.generar(101) < 75) {
      return EEstado::PARALIZADO;
    }
    return EEstado::NORMAL;
  }
  return EEstado::NORMAL;
}

// METODOS PRIVADOS
// -------------------------

int LogicaAtaque::calcularDanioBase(const std::shared_ptr<Pokemon> &atacante,
                                    const std::shared_ptr<Pokemon> &defensor,
                                    const Movimiento &ataque) {
  int valorAtaquePokemon = atacante->getValorAtaque();
  int valorDefensaPokemon = defensor->getValorDefensa();

  if (ataque.esEspecial()) {
    valorAtaquePokemon = atacante->getValorAtaqueEspecial();
    valorDefensaPokemon = defensor->getValorDefensaEspecial();
  }

  // Aseguramos que el cálculo sea seguro y prevenimos divisiones por cero
  if (valorDefensaPokemon == 0) {
    throw std::runtime_error("Error: Defensa del Pokémon defensor es 0.");
  }

  int calculo =
      (ataque.getDanio() * valorAtaquePokemon *
       Efectividad::getEfectividad(atacante->getTipo(), defensor->getTipo())) /
      valorDefensaPokemon;

  return calculo;
}

std::string LogicaAtaque::aplicarEfectosEstado(std::shared_ptr<Pokemon> pok,
                                               const Movimiento &ataque) {

  if (pok->getEstado() == EEstado::NORMAL && ataque.esEspecial()) {
    pok->setEstado(ataque.getEfecto());
    return format(
        "{} ha sido **{}**:exclamation:\n", pok->getNombre(),
        EnumTools::estadoToString(
            ataque.getEfecto())); // ToDo: Buscar la mejor forma de hacer
                                  // públicamente accesible toString de Menu.cpp
  }
  return "";
}

void LogicaAtaque::actualizarContadores(std::shared_ptr<Entrenador> &ente,
                                        const Movimiento &ataque) {
  int contadorEspecial = ente->getContadorEspecial();
  ente->setContadorEspecial(ataque.esEspecial()
                                ? (contadorEspecial == 0 ? 2 : contadorEspecial)
                                : std::max(0, contadorEspecial - 1));
}

bool LogicaAtaque::esCritico() {
  if (generador.generar(101) < 10) {

    return true;
  }
  return false;
}
