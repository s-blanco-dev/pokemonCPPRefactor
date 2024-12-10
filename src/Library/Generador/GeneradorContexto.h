//
// Created by jwillmore on 12/6/24.
//

#ifndef GENERADORCONTEXTO_H
#define GENERADORCONTEXTO_H
#include <memory>

#include "IGenerador.h"


class GeneradorContexto {
private:
    IGenerador* generador;

public:
    explicit GeneradorContexto(IGenerador* gen);

    void cambiarGenerador(IGenerador* nuevoGen);
    int generar(int num);
};

#endif //GGENERADORCONTEXTO_H
