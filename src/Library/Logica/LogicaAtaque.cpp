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
#include <sstream>

// CONSTRUCTOR
// -------------------------
LogicaAtaque::LogicaAtaque(IGenerador* gen):
generador(gen) {
  this->tablaEfectividad = Efectividad();
}

// METODOS PUBLICOS
// -------------------------
std::string LogicaAtaque::aplicarAtaque(std::shared_ptr<Entrenador> atacante, std::shared_ptr<Entrenador> defensor, const Movimiento& ataque) {
    // Usamos std::shared_ptr para gestionar la propiedad de los Pokémon activos
    auto pokemonAtaque = atacante->getPokemonActivo();
    auto pokemonDefensa = defensor->getPokemonActivo();

    if (!pokemonAtaque || !pokemonDefensa) {
        throw std::runtime_error("Error: Pokémon activo no válido.");
    }

    int danioBase = calcularDanioBase(pokemonAtaque, pokemonDefensa, ataque);

    std::ostringstream mensaje; // Usamos std::ostringstream para evitar errores al concatenar strings
    mensaje << atacante->getNombre() << " ha usado " << ataque.getNombre() << "!\n";

    if (esCritico()) {
        mensaje << "ATAQUE CRÍTICO";
        danioBase *= 2;
    }

    pokemonDefensa->recibirDanio(danioBase);

    return mensaje.str();
}

// METODOS PRIVADOS
// -------------------------

int LogicaAtaque::calcularDanioBase(std::shared_ptr<Pokemon> atacante, std::shared_ptr<Pokemon> defensor, const Movimiento& ataque) {
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

    int calculo = (ataque.getDanio() * valorAtaquePokemon *
                   tablaEfectividad.getEfectividad(atacante->getTipo(), defensor->getTipo())) / valorDefensaPokemon;

    return calculo;
}


bool LogicaAtaque::esCritico()
{
  if (generador.generar(101) < 10) {
  
    return true;
  }
  return false;
}

