#include "Placaje.h"
#include "../../Logica/Movimiento.h"

Placaje::Placaje() : Movimiento() {
  this->nombre = "Placaje";
  this->tipo = ETipos::NORMAL;
  this->danio = 50;
  this->precision = 90;
  this->PP = 8;
  this->currentPP = this->PP;
}
