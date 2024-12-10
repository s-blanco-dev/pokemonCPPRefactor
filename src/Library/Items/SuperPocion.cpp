//
// Created by jwillmore on 12/6/24.
//

#include "SuperPocion.h"
#include <string>
using namespace std;

// GETTERS
string SuperPocion::getNombre() const{
    return nombre;
}

string SuperPocion::getDescripcion() const {
    return descripcion;
}

// CONSTRUCTOR
SuperPocion::SuperPocion() {
    this->nombre = "SuperPocion";
    this->descripcion = "Poción que marcha joya";
}

// METODOS PUBLICOS
void SuperPocion::usarIItem(Pokemon& pokemon) {
    pokemon.setHP(pokemon.getHP() + 20);
}





