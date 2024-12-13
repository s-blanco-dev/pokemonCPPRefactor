#include "BolaVoltio.h"
#include "../../Logica/Movimiento.h"

BolaVoltio::BolaVoltio() : Movimiento() {
  this->nombre = "Bola Voltio";
  this->tipo = ETipos::ELECTRICO;
  this->danio = 75;
  this->precision = 90;
  this->PP = 4;
  this->currentPP = this->PP;
}
