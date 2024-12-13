#include "Aurorus.h"
#include "../Logica/Pokemon.h"
#include "../Movimientos/Hielo/RayoGelido.h"
#include "../Movimientos/Normal/Placaje.h"

Aurorus::Aurorus() : Pokemon() {
  this->nombre = "Aurorus";
  this->tipo = ETipos::HIELO;
  this->hPMax = 201;
  this->hP = this->hPMax;
  this->valorAtaque = 53;
  this->valorDefensa = 62;
  this->valorAtaqueEspecial = 58;
  this->valorDefensaEspecial = 63;
  this->movimientos = {RayoGelido(), Placaje()};
};
