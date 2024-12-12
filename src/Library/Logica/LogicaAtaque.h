//
// Created by jwillmore on 12/7/24.
//

#ifndef LOGICAATAQUE_H
#define LOGICAATAQUE_H
#include "Entrenador.h"
#include "../Generador/GeneradorContexto.h"
#include "../Generador/IGenerador.h"
#include "Movimiento.h"
#include "Pokemon.h"
#include "../Contenedores/Efectividad.h"

class LogicaAtaque {
private:
  GeneradorContexto generador;

  int calcularDanioBase(const std::shared_ptr<Pokemon> &atacante, const std::shared_ptr<Pokemon> &defensor, const Movimiento& ataque);
  bool esCritico();

    public:
    LogicaAtaque(IGenerador* gen);

    std::string aplicarAtaque(const std::shared_ptr<Entrenador> &atacante, const std::shared_ptr<Entrenador> &defensor, const Movimiento& ataque);
    std::string verificarEstadoPokemon(Pokemon& pok);


};



#endif //LOGICAATAQUE_H
