//
// Created by jwillmore on 12/6/24.
//

#include "GeneradorAleatorio.h"
#include <ctime>
#include <cstdlib>

GeneradorAleatorio::GeneradorAleatorio() {
    std::srand(std::time(nullptr));
};

int GeneradorAleatorio::generarNum(int num) const {
    return std::rand() % num;
}
