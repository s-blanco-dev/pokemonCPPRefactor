//
// Created by jwillmore on 12/5/24.
//

#include "Pikachu.h"
#include "../Logica/Pokemon.h"
#include "../Movimientos/Fuego/Lanzallamas.h"


Pikachu::Pikachu(): Pokemon() {
    this->nombre = "Pikachu";
    this->tipo = ETipos::ELECTRICO;
    this->hPMax = 180;
    this->hP = this->hPMax;
    this->valorAtaque = 56;
    this->valorDefensa = 50;
    this->valorAtaqueEspecial = 60;
    this->valorDefensaEspecial = 53;
    this->movimientos = {Lanzallamas()};
   } ;
