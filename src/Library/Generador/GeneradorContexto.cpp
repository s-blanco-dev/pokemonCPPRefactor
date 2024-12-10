//
// Created by jwillmore on 12/6/24.
//

#include "GeneradorContexto.h"

GeneradorContexto::GeneradorContexto(IGenerador* gen) {
    this->generador = gen;
}

void GeneradorContexto::cambiarGenerador(IGenerador* nuevoGen) {
    this->generador = nuevoGen;
}

int GeneradorContexto::generar(int num) {
    return generador->generarNum(num);
}


