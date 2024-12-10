//
// Created by jwillmore on 12/6/24.
//

#ifndef GENERADORALEATORIO_H
#define GENERADORALEATORIO_H
#include "IGenerador.h"


class GeneradorAleatorio : public IGenerador {
    public:
    GeneradorAleatorio();
    int generarNum(int num) const override;

};



#endif //GENERADORALEATORIO_H
