#include "Rayo.h"
#include "../../Logica/Movimiento.h"

Rayo::Rayo() : Movimiento() {
  this->nombre = "Rayo";
  this->especial = true;
  this->tipo = ETipos::ELECTRICO;
  this->efecto = EEstado::PARALIZADO;
  this->danio = 90;
  this->precision = 75;
  this->PP = 2;
  this->currentPP = this->PP;
}
