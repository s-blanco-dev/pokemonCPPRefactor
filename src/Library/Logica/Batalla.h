//
// Created by jwillmore on 12/6/24.
//

#ifndef BATALLA_H
#define BATALLA_H
#include "../Contenedores/Pokedex.h"
#include "../Generador/GeneradorContexto.h"
#include "../Generador/IGenerador.h"
#include "Entrenador.h"
#include "LogicaAtaque.h"
#include "Movimiento.h"
#include <string>

class Batalla {
private:
  // ATRIBUTOS PRIVADOS
  std::shared_ptr<Entrenador>
      entrenador_1; // Los shared_ptr evitaron que me volara la cabeza
  std::shared_ptr<Entrenador> entrenador_2;
  std::shared_ptr<Entrenador> entrenadorActual;
  Pokedex *pokedex; // Inicializo en constructor
  int contadorTurno;
  GeneradorContexto generador;
  LogicaAtaque _logica;

  // METODOS PRIVADOS
  bool finBatalla();
  void siguienteTurno();

public:
  Entrenador getEntrenadorActual() const;
  void setEntrenadorActual(Entrenador &ent);

  Batalla(std::shared_ptr<Entrenador> ent1, std::shared_ptr<Entrenador> ent2,
          IGenerador *gen);
  std::string iniciarBatalla();

  std::string atacar(std::shared_ptr<Entrenador> &atacante, Movimiento &ataque);
  std::string seleccionarPokemon(const std::shared_ptr<Entrenador> &ente,
                                 Pokemon &pok);
  std::shared_ptr<Entrenador> obtenerEntrenadorPorNombre(std::string nombre);

  bool esTurnoDe(Entrenador &entrenador);
};

#endif // BATALLA_H
