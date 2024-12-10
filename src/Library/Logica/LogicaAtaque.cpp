//
// Created by jwillmore on 12/7/24.
//

#include "LogicaAtaque.h"
#include "../Generador/GeneradorContexto.h"
#include "../Generador/IGenerador.h"
#include "Pokemon.h"
#include "Movimiento.h"
#include "../Contenedores/Efectividad.h"
#include <format>

// CONSTRUCTOR
// -------------------------
LogicaAtaque::LogicaAtaque(IGenerador* gen):
generador(gen) {
  this->tablaEfectividad = Efectividad();
}

// METODOS PUBLICOS
// -------------------------
std::string LogicaAtaque::aplicarAtaque(Entrenador &atacante, Entrenador &defensor, Movimiento ataque) {
    std::string mensaje = "";

    Pokemon& pokemonAtaque = atacante.getPokemonActivo();
    Pokemon& pokemonDefensa = defensor.getPokemonActivo();

    int danioBase = calcularDanioBase(pokemonAtaque, pokemonDefensa, ataque);

    mensaje += format("{} ha usado {}!\n", atacante.getNombre(), ataque.getNombre());

    if (esCritico()) {
      mensaje += "ATAQUE CRÍTICO!\n";
      danioBase *= 2;
    }

    pokemonDefensa.recibirDanio(danioBase);

    return mensaje;
}

// METODOS PRIVADOS
// -------------------------

int LogicaAtaque::calcularDanioBase(Pokemon atacante, Pokemon defensor, Movimiento ataque) {
    int valorAtaquePokemon = atacante.getValorAtaque();
    int valorDefensaPokemon = defensor.getValorDefensa();

    if (ataque.esEspecial()) {
        valorAtaquePokemon = atacante.getValorAtaqueEspecial();
        valorDefensaPokemon = defensor.getValorDefensaEspecial();
    }

    int calculo = (ataque.getDanio() * valorAtaquePokemon * tablaEfectividad.getEfectividad(atacante.getTipo(), defensor.getTipo())) / valorDefensaPokemon; 

    return calculo;
}

bool LogicaAtaque::esCritico()
{
  if (generador.generar(101) < 10) {
  
    return true;
  }
  return false;
}

