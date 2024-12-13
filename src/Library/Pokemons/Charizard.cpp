//
// Created by jwillmore on 12/5/24.
//

#include "Charizard.h"
#include "../Movimientos/Fuego/Lanzallamas.h"
#include "../Movimientos/Normal/Placaje.h"

Charizard::Charizard() : Pokemon() {
  this->nombre = "Charizard";
  this->tipo = ETipos::FUEGO;
  this->hPMax = 197;
  this->hP = this->hPMax;
  this->valorAtaque = 61;
  this->valorDefensa = 50;
  this->valorAtaqueEspecial = 68;
  this->valorDefensaEspecial = 54;
  this->movimientos = {Lanzallamas(), Placaje()};
};
