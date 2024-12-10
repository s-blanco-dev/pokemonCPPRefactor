//
// Created by jwillmore on 12/8/24.
//

#ifndef FACADE_H
#define FACADE_H
#include "../Generador/GeneradorContexto.h"
#include "../Logica/Batalla.h"
#include "../Logica/Entrenador.h"
#include "../Contenedores/Pokedex.h"
#include <string>
#include <vector>



class Facade {
  private:
    static Facade* instance; 
    Batalla* batallaActual;
    Pokedex* pokedexActual;
    vector<Entrenador> listaEspera;
    // Menu
    // Lista de espera

    Facade();

    Entrenador* buscarEntrenadorPorNombre(std::string nombre);

  public:
    static Facade* getInstance();
    std::string unirBatalla(std::string nombreEntrenador);
    std::string seleccionarPokemon(std::string nombrePokemon, std::string nombreEnt);
    std::string iniciarBatalla(IGenerador* generador);
    std::string atacar(std::string nombreEnt, Movimiento movimiento);
};



#endif //FACADE_H
