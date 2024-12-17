#include "Gyarados.h"
#include "../Logica/Pokemon.h"
#include "../Movimientos/Agua/Hidropulso.h"
#include "../Movimientos/Electrico/Rayo.h"
#include "../Movimientos/Normal/Placaje.h"

Gyarados::Gyarados() : Pokemon() {
  this->nombre = "Gyarados";
  this->tipo = ETipos::VOLADOR;
  this->hPMax = 190;
  this->hP = this->hPMax;
  this->valorAtaque = 60;
  this->valorDefensa = 60;
  this->valorAtaqueEspecial = 64;
  this->valorDefensaEspecial = 64;
  this->movimientos = {Rayo(), Hidropulso(), Placaje()};
};
