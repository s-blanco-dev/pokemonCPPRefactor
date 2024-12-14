//
// Created by jwillmore on 12/8/24.
//

#ifndef FACADE_H
#define FACADE_H
#include "../Contenedores/Pokedex.h"
#include "../Generador/GeneradorContexto.h"
#include "../Logica/Batalla.h"
#include "../Logica/Entrenador.h"
#include <string>
#include <vector>

#include "Menu.h"

class Facade {
private:
  static Facade *instance;
  Batalla *batallaActual;
  Pokedex *pokedexActual;
  std::vector<Entrenador> listaEspera;
  Menu *menuActual;

  Facade();

  Entrenador *buscarEntrenadorPorNombre(std::string nombre);

  static Movimiento *buscarMovimientoPorNombre(std::string nombre,
                                               Entrenador ente);

public:
  static Facade *getInstance(); // instancia única de Singleton
  static void
  resetInstance(); // Resetea la instancia (para nueva batalla desde cero)
  ~Facade();       // Destructor

  std::string unirBatalla(std::string nombreEntrenador);
  std::string seleccionarPokemon(std::string nombrePokemon,
                                 std::string nombreEnt);
  std::string iniciarBatalla(IGenerador *generador);
  std::string atacar(std::string nombreEnt, std::string nombreMov);
  std::string mostrarPokedex();
  std::string desplegarMenuAtaque(std::string nombreEnt);
};

#endif // FACADE_H
