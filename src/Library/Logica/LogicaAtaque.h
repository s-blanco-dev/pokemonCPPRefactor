//
// Created by jwillmore on 12/7/24.
//

#ifndef LOGICAATAQUE_H
#define LOGICAATAQUE_H
#include "../Contenedores/Efectividad.h"
#include "../Generador/GeneradorContexto.h"
#include "../Generador/IGenerador.h"
#include "Entrenador.h"
#include "Movimiento.h"
#include "Pokemon.h"
#include <memory>
#include <string>

class LogicaAtaque {
private:
  GeneradorContexto generador;

  int calcularDanioBase(const std::shared_ptr<Pokemon> &atacante,
                        const std::shared_ptr<Pokemon> &defensor,
                        const Movimiento &ataque);
  bool esCritico();
  std::string aplicarEfectosEstado(std::shared_ptr<Pokemon> pok,
                                   const Movimiento &ataque);
  void actualizarContadores(std::shared_ptr<Entrenador> &ente,
                            const Movimiento &ataque);

public:
  LogicaAtaque(IGenerador *gen);

  std::string aplicarAtaque(std::shared_ptr<Entrenador> &atacante,
                            const std::shared_ptr<Entrenador> &defensor,
                            const Movimiento &ataque);
  EEstado verificarEstadoPokemon(std::shared_ptr<Pokemon> &pok);
};

#endif // LOGICAATAQUE_H
