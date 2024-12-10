//
// Created by jwillmore on 12/6/24.
//

#ifndef BATALLA_H
#define BATALLA_H
#include "Entrenador.h"
#include "../Contenedores/Pokedex.h"
#include "../Generador/GeneradorContexto.h"
#include "../Generador/IGenerador.h"
#include "Movimiento.h"
#include "LogicaAtaque.h"
#include <string>


class Batalla {
private:
    // ATRIBUTOS PRIVADOS
    Entrenador& entrenador_1;
    Entrenador& entrenador_2;
    Entrenador* entrenadorActual;
    Pokedex *pokedex; // Inicializo en constructor
    int contadorTurno;
    GeneradorContexto generador;
    LogicaAtaque _logica;

    // METODOS PRIVADOS
    bool esTurnoDe(Entrenador &entrenador);
    bool finBatalla();
    void siguienteTurno();

public:
    Entrenador getEntrenadorActual() const;
    void setEntrenadorActual(Entrenador &ent);

    Batalla(Entrenador &ent1, Entrenador &ent2, IGenerador* gen);
    std::string iniciarBatalla();

    std::string atacar(Entrenador &atacante, Movimiento &ataque);
    std::string seleccionarPokemon(Entrenador &ente, Pokemon &pok);
};



#endif //BATALLA_H
