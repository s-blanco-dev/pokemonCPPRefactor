//
// Created by jwillmore on 12/6/24.
//

#include "SuperPocion.h"
#include <algorithm>
#include <stdexcept>
#include <string>

// GETTERS y SETTERS
std::string SuperPocion::getNombre() const { return nombre; }

std::string SuperPocion::getDescripcion() const { return descripcion; }

int SuperPocion::getUsos() const { return this->usos; }
int SuperPocion::getUsosMax() const { return this->usosMax; }
void SuperPocion::setUsos(int usos) { this->usos = usos; }

// CONSTRUCTOR
SuperPocion::SuperPocion() {
  this->nombre = "SuperPocion";
  this->descripcion = "Restaura 70 HP y marcha joya";
  this->usosMax = 3;
  this->usos = this->usosMax;
}

// METODOS PUBLICOS
void SuperPocion::usarIItem(Pokemon &pokemon) {
  if (this->usos > 0) {
    pokemon.setHP(std::min((pokemon.getHP() + 70), pokemon.getHPMax()));
    this->usos -= 1;
  } else {
    throw std::invalid_argument("Se te terminó la piola, muchacho.");
  }
}
