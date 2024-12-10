//
// Created by jwillmore on 12/5/24.
//

#include "../../Logica/Movimiento.h"
#include "Lanzallamas.h"

Lanzallamas::Lanzallamas() : Movimiento() {
    this->nombre = "Lanzallamas";
    this->especial = true;
    this->tipo = ETipos::FUEGO;
    this->efecto = EEstado::QUEMADO;
    this->danio = 85;
    this->precision = 95;
    this->PP = 3;
    this->currentPP = this->PP;
}

