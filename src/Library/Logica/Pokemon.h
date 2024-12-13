//
// Created by jwillmore on 12/5/24.
//
#ifndef POKEMON_H
#define POKEMON_H
#include <string>
#include <vector>

#include "../Enums/ETipos.h"
#include "Movimiento.h"
using namespace std;


class Pokemon {
    protected:
    // ATRIBUTOS PROTEGIDOS
    string nombre;
    int hPMax;
    int hP;
    bool debil;
    int valorAtaque;
    int valorDefensa;
    int valorAtaqueEspecial;
    int valorDefensaEspecial;
    int turnosDormido;
    vector<Movimiento> movimientos;
    ETipos tipo;
    EEstado estado;

    public:

    // GETTERS y SETTERS
    string getNombre() const;
    void setHP(int hP);
    int getHP();
    int getHPMax() const;
    void setDebil(bool debil);
    bool isDebil() const;
    int getValorAtaque() const;
    int getValorDefensa() const;
    int getValorAtaqueEspecial() const;
    int getValorDefensaEspecial() const;
    int getTurnosDormido();
    void setTurnosDormido(int turnos);
    ETipos getTipo() const;
    EEstado getEstado() const;
    void setEstado(EEstado estado);
    vector<Movimiento>& getMovimientos();

    // CONSTRUCTOR
    Pokemon();

    // METODOS PUBLICOS
    void recibirDanio(int danio);
};

#endif //POKEMON_H
