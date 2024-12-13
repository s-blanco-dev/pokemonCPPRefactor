#include "PlacajeElectrico.h"
#include "../../Logica/Movimiento.h"

PlacajeElectrico::PlacajeElectrico() : Movimiento() {
  this->nombre = "Placaje Electrico";
  this->tipo = ETipos::ELECTRICO;
  this->danio = 90;
  this->precision = 75;
  this->PP = 2;
  this->currentPP = this->PP;
}
