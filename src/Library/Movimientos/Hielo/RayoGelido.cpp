#include "RayoGelido.h"
#include "../../Logica/Movimiento.h"

RayoGelido::RayoGelido() : Movimiento() {
  this->nombre = "Rayo Gelido";
  this->tipo = ETipos::HIELO;
  this->danio = 100;
  this->precision = 80;
  this->PP = 2;
  this->currentPP = this->PP;
}
