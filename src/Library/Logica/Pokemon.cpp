//
// Created by jwillmore on 12/5/24.
//
#include "Pokemon.h"
#include <iostream>
using namespace std;


// GETTERS y SETTERS
// -------------------------
string Pokemon::getNombre() const{
    return this->nombre;
}

bool Pokemon::isDebil() const {
    return this->debil;
}

int Pokemon::getHP(){
    return this->hP;
}

int Pokemon::getHPMax() const{
    return this->hPMax;
}

void Pokemon::setHP(int hP) {
    this->hP = hP;
}

void Pokemon::setDebil(bool debil) {
    this->debil = debil;
}

ETipos Pokemon::getTipo() const{
    return this->tipo;
}

EEstado Pokemon::getEstado() const {
    return this->estado;
}

void Pokemon::setEstado(EEstado estado) {
    this->estado = estado;
}


vector<Movimiento>& Pokemon::getMovimientos() {
    return this->movimientos;
}

int Pokemon::getValorAtaque() const {
    return this->valorAtaque;
}

int Pokemon::getValorDefensa() const {
    return this->valorDefensa;
}

int Pokemon::getValorAtaqueEspecial() const {
    return this->valorAtaqueEspecial;
}

int Pokemon::getValorDefensaEspecial() const {
    return this->valorDefensaEspecial;
}




// CONSTRUCTOR
// -------------------------
Pokemon::Pokemon() {
    this->debil = false;
}

// METODOS PUBLICOS
// -------------------------

void Pokemon::recibirDanio(int danio) {
    this->hP = max(hP - danio, 0);

    if (this->hP == 0) {
        this-> debil = true;
    }
}




