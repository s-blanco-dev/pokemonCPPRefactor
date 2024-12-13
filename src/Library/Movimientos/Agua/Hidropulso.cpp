#include "Hidropulso.h"
#include "../../Logica/Movimiento.h"

Hidropulso::Hidropulso() : Movimiento() {
  this->nombre = "Hidropulso";
  this->especial = true;
  this->tipo = ETipos::AGUA;
  this->efecto = EEstado::DORMIDO;
  this->danio = 65;
  this->precision = 90;
  this->PP = 4;
  this->currentPP = this->PP;
}
