//
// Created by jwillmore on 12/8/24.
//

#include "Efectividad.h"

const std::map<std::pair<ETipos, ETipos>, double> Efectividad::efect = {
    {{ETipos::FUEGO, ETipos::PLANTA}, 2.0},
    {{ETipos::FUEGO, ETipos::AGUA}, 0.5},
    {{ETipos::AGUA, ETipos::FUEGO}, 2.0},
    {{ETipos::PLANTA, ETipos::ROCA}, 2.0}
};

Efectividad::Efectividad() {
}

double Efectividad::getEfectividad(ETipos atacante, ETipos defensor) {
    auto it = efect.find({atacante, defensor});
    if (it != efect.end()) {
        return it->second;
    }
    return 1.0; // Efectividad neutral por defecto
}