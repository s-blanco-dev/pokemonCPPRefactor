//
// Created by jwillmore on 12/6/24.
//

#include "Batalla.h"
#include "../Generador/GeneradorContexto.h"
#include "../Generador/IGenerador.h"
#include "../Contenedores/Pokedex.h"
#include "LogicaAtaque.h"
#include "Movimiento.h"
#include "Pokemon.h"
#include <format>
#include <string>

// GETTERS Y SETTERS
// -------------------------
// void Batalla::setEntrenadorActual(Entrenador &ent){
//   this->entrenadorActual = ent;
// }

Entrenador Batalla::getEntrenadorActual() const{
  return *entrenadorActual;
}

// CONSTRUCTOR
// -------------------------
Batalla::Batalla(std::shared_ptr<Entrenador> ent1, std::shared_ptr<Entrenador> ent2, IGenerador* gen): entrenador_1(ent1),
    entrenador_2(ent2),
    entrenadorActual(ent1), // Por defecto inicializo el entrenador1 como actual
    pokedex(Pokedex::getInstance()), 
    contadorTurno(0),
    generador(GeneradorContexto(gen)),
_logica(LogicaAtaque(gen)){
}

// METODOS PUBLICOS
// -------------------------
std::string Batalla::iniciarBatalla() {
    if (generador.generar(2) == 0) {
        entrenadorActual = entrenador_2;
    } else {
        entrenadorActual = entrenador_1;
    }

    return format("Atención **{}** y **{}**, ha empezado la batalla! :trumpet: \nEs turno de **{}**",
                  entrenador_1->getNombre(), entrenador_2->getNombre(), entrenadorActual->getNombre());
}

// 3 días para hacer funcionar lo más básico del metodo atacar -> mi familia me reservó un cuarto en el Vilardebó
std::string Batalla::atacar(std::shared_ptr<Entrenador> atacante, Movimiento &ataque)
{
    try {
        std::string mensaje = "";
        std::shared_ptr<Entrenador> defensor = entrenador_1;

        if (!esTurnoDe(*atacante)) {
            throw std::invalid_argument(format("No es tu turno, {}!", atacante->getNombre()));
        } // verifica que sea el turno del entrenador

        if (atacante->getPokemonActivo()->isDebil())
        {
            throw std::invalid_argument(format(":prohibited: {} está debilitado :prohibited:", atacante->getPokemonActivo()->getNombre()));
        } // No ataca si el pokemon está debil

        if (atacante->getNombre() == entrenador_1->getNombre())
        {
            defensor = entrenador_2;
        } // por lógica, si el entrenador1 es el atacante, entonces el entrenador2 es el defensor

        if (defensor->getPokemonActivo()->isDebil())
        {
            throw std::invalid_argument(format(":prohibited: **{}** está debilitado :prohibited:", defensor->getPokemonActivo()->getNombre()));
        } // Tampoco ataca si el pokemon del defensor está debil

        if (ataque.esEspecial() && atacante->getContadorEspecial() != 0)
        {
            throw invalid_argument(format(":prohibited: Debes esperar **{}** turnos más para usar un ataque especial :prohibited:", atacante->getContadorEspecial()));
        } // verifica que pueda usar ataque especial

        if (ataque.getCurrentPP() == 0)
        {
            throw invalid_argument(format("**{}** está agotado:exclamation:", ataque.getNombre()));
        } // verifica que tenga ataques disponibles

        // ---
        // PENDIENTE: verificar estado de pokemon en LogicaAtaque
        // ---

        // aplica el ataque recibiendo referencias a ambos pokemones
        mensaje += _logica.aplicarAtaque(atacante, defensor, ataque);

        ataque.setCurrentPP(ataque.getPP() - 1); // Reduce en 1 el contador de usos disponibles para el ataque

        siguienteTurno();
        return mensaje;
    }
    catch (const std::exception &e) {
        return e.what();
    }
}


// Bitácora del 10/12/2024:
// Primer intento de suicidio
// Hace 4 días que no puedo solucionar el bug
// Se selecciona Pikachu pero mágicamente se convierte en Charizard
// PD: lo solucioné, nuevamente los punteros y referencias me generaron un aneurisma

std::string Batalla::seleccionarPokemon(std::shared_ptr<Entrenador> ente, Pokemon &pok) {
    auto copiaPokemon = std::make_shared<Pokemon>(pok);

    if (pokedex->getPokemonByName(pok.getNombre()) == nullptr) {
        return "El pokemon no está disponible!";
    }

    ente->agregarPokemon(copiaPokemon); // Usar la copia
    pokedex->removePokemon(pok); // Eliminar el original de la Pokédex
    ente->setPokemonActivo(copiaPokemon); // Usar la copia como activo

    return format("{} ha seleccionado a {} para su equipo!\n", ente->getNombre(), copiaPokemon->getNombre());
    // FINALMENTE FUNCIONA -> (3 días programando en C++ derivaron en 7 años de estancia en el Vilardebó)
}

std::shared_ptr<Entrenador> Batalla::obtenerEntrenadorPorNombre(std::string nombre) {
    if (nombre == entrenador_1->getNombre()) {return entrenador_1;}
    return entrenador_2;
}



// METODOS PRIVADOS
// -------------------------

bool Batalla::esTurnoDe(Entrenador &entrenador){
    return (entrenador.getNombre() == entrenadorActual->getNombre());
}


bool Batalla::finBatalla() {
    for (auto p : entrenador_1->getPokemons()) {
        if (!p->isDebil()) {return false;}
    }
    for (auto p : entrenador_2->getPokemons()) {
        if (!p->isDebil()) {return false;}
    }
    return true;
}

void Batalla::siguienteTurno() {
  this->contadorTurno++;
  this->entrenadorActual = (entrenadorActual->getNombre() == entrenador_1->getNombre()) ? entrenador_2 : entrenador_1;
}
