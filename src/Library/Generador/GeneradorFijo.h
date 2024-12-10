//
// Created by jwillmore on 12/6/24.
//

#ifndef GENERADORFIJO_H
#define GENERADORFIJO_H
#include "IGenerador.h"


class GeneradorFijo : public IGenerador{
public:
    GeneradorFijo();
    int generarNum(int num) const override;
};

#endif //GENERADORFIJO_H
