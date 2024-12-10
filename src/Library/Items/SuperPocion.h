//
// Created by jwillmore on 12/6/24.
//

#ifndef SUPERPOCION_H
#define SUPERPOCION_H
#include "../Interfaces/IItem.h"
using namespace std;


class SuperPocion : public IItem{
    private:
    string nombre;
    string descripcion;

    public:
    SuperPocion();

    string getNombre() const override;
    string getDescripcion() const override;
    void usarIItem(Pokemon& pokemon) override;
};

#endif //SUPERPOCION_H
