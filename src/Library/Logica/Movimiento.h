//
// Created by jwillmore on 12/5/24.
//

#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H
using namespace std;

#include <string>
#include "../Enums/ETipos.h"  // Asegúrate de tener este enum definido
#include "../Enums/EEstado.h"  // Asegúrate de tener este enum definido

class Movimiento {
protected:
    // Atributos
    std::string nombre;
    ETipos tipo;
    double danio;
    int PP;
    int currentPP;
    bool especial;
    EEstado efecto = EEstado::NORMAL;
    double precision;

public:
    // Getters
    std::string getNombre() const;
    ETipos getTipo() const;
    double getDanio() const;
    int getPP() const;
    int getCurrentPP() const;
    bool esEspecial() const;
    double getPrecision() const;
    EEstado getEfecto() const;

    // Constructor
    Movimiento();

    // Setters
    void setCurrentPP(int currentPP);
};

#endif // MOVIMIENTO_H
