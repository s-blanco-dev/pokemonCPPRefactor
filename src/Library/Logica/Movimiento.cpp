//
// Created by jwillmore on 12/5/24.
//

#include "Movimiento.h"

#include "../Movimientos/Fuego/Lanzallamas.h"

// Getters
std::string Movimiento::getNombre() const {
    return nombre;
}

ETipos Movimiento::getTipo() const {
    return tipo;
}

double Movimiento::getDanio() const {
    return danio;
}

int Movimiento::getPP() const {
    return PP;
}

int Movimiento::getCurrentPP() const {
    return currentPP;
}

bool Movimiento::esEspecial() const {
    return especial;
}

double Movimiento::getPrecision() const {
    return precision;
}

EEstado Movimiento::getEfecto() const {
    return efecto;
}

// CONSTRUCTOR
Movimiento::Movimiento() {
    this->especial = false;
    this->efecto = EEstado::NORMAL;
}


// Setter
void Movimiento::setCurrentPP(int currentPP) {
    this->currentPP = currentPP;
}