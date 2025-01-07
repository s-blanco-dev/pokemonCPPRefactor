//
// Created by jwillmore on 12/8/24.
//

#ifndef FACADE_H
#define FACADE_H
#include "../Contenedores/Pokedex.h"
#include "../Generador/GeneradorContexto.h"
#include "../Logica/Batalla.h"
#include "../Logica/Entrenador.h"
#include <memory>
#include <optional>
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

  void existeBatalla();
  std::optional<Entrenador> buscarEntrenadorPorNombre(std::string nombre);
  static std::optional<Movimiento> buscarMovimientoPorNombre(std::string nombre,
                                                             Entrenador ente);
  void existeEntrenador(const std::shared_ptr<Entrenador> &ente);
  void tienePokemonActivo(const std::shared_ptr<Entrenador> &ente);
  IItem *obtenerItemPorNombre(const std::shared_ptr<Entrenador> &ente,
                              std::string nombreItem);

public:
  static Facade *getInstance(); // instancia única de Singleton
  static void
  resetInstance(); // Resetea la instancia (para nueva batalla desde cero)
  ~Facade();       // Destructor
  Batalla *getBatalla();

  std::string unirBatalla(std::string nombreEntrenador);
  std::string seleccionarPokemon(std::string nombrePokemon,
                                 std::string nombreEnt);
  std::string iniciarBatalla(IGenerador *generador);
  std::string atacar(std::string nombreEnt, std::string nombreMov);
  std::string mostrarPokedex();
  std::string desplegarMenuAtaque(std::string nombreEnt);
  std::string cambiarPokemon(std::string nombrePokemon,
                             std::string nombreEntrenador);
  std::string misPokemon(std::string nombreEntrenador);
  std::string usarItem(std::string nombreEntrenador, std::string nombreItem);
  std::string menuItems(std::string nombreEntrenador);
};

#endif // FACADE_H
