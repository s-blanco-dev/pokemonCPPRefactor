//
// Created by jwillmore on 12/8/24.
//

#ifndef EFECTIVIDAD_H
#define EFECTIVIDAD_H
#include <map>
#include <unordered_map>

#include "../Enums/ETipos.h"


class Efectividad {
public:
    static const std::map<std::pair<ETipos, ETipos>, double> efect;

    Efectividad();

    static double getEfectividad(ETipos atacante, ETipos defensor);
};


#endif //EFECTIVIDAD_H
