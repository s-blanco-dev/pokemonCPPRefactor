//
// Created by jwillmore on 12/8/24.
//

#include "Facade.h"
#include <string>
#include <vector>
#include <format>

// Bitácora del 9/12/2024:
// Fui diagnosticado con esquizofrenia paranoide
// Los punteros inteligentes me siguien hasta en el supermercado
// no veo la luz desde hace 2 semanas

Facade* Facade::instance = nullptr;

Facade::Facade() {
  this->pokedexActual = Pokedex::getInstance();
  this->batallaActual = nullptr;
  this->listaEspera = vector<Entrenador>();
}

Facade* Facade::getInstance(){
  if (instance == nullptr)
        {
            instance = new Facade();
        }
        return instance;
}

std::string Facade::unirBatalla(std::string nombreEnt){
  listaEspera.push_back(Entrenador(nombreEnt));

  return format("**{}** está esperando para batallar :crossed_swords:\n", nombreEnt);
}

std::string Facade::iniciarBatalla(IGenerador* gen){
 auto ent1 = std::make_shared<Entrenador>(listaEspera[0]);
 auto ent2 = std::make_shared<Entrenador>(listaEspera[1]);

 batallaActual = new Batalla(ent1, ent2, gen);
 return  batallaActual->iniciarBatalla();
}

std::string Facade::seleccionarPokemon(std::string nombrePok, std::string nombreEnt) {
  try {
    auto ente = batallaActual->obtenerEntrenadorPorNombre(nombreEnt);
    Pokemon* pokemon = pokedexActual->getPokemonByName(nombrePok);

    if (pokemon == nullptr) {
      return "El pokemon no está disponible";
    }

    // Pasar punteros directamente a Batalla
    return batallaActual->seleccionarPokemon(ente, *pokemon);
  }
  catch (std::exception& e) {
    return e.what();
  }
}

// Bitácora del 11/12/2024
// Las alucinaciones no dan tregüa
// luego de 3 días de debugging, logré hacer funcionar el metodo atacar
// Nota: NO USAR REFERENCIAS Y PUNTEROS CRUDOS. EN LO POSIBLE USAR SHARED_PTR
std::string Facade::atacar(std::string nombreEnt, std::string nombreMov) {
  try {
    auto ente = batallaActual->obtenerEntrenadorPorNombre(nombreEnt);
    if (ente == nullptr) {
      throw std::invalid_argument("Entrenador no encontrado!");
    }

    auto ataque = buscarMovimientoPorNombre(nombreMov, *ente);
    if (ataque == nullptr) {
      throw std::invalid_argument("Movimiento no encontrado!");
    }

    return batallaActual->atacar(ente, *ataque);
  }
  catch (std::exception& e) {
    return e.what();
  }
}


// METODOS PRIVADOS
// -------------------------
Entrenador* Facade::buscarEntrenadorPorNombre(std::string nombre){
  for (Entrenador &ent : this->listaEspera)
  {
    if (nombre == ent.getNombre())
    {
      return &ent;
    }
  }
  return nullptr;
}

std::shared_ptr<Movimiento> Facade::buscarMovimientoPorNombre(std::string nombre, Entrenador ente) {
  std::vector<Movimiento> movs = ente.obtenerMovimientosPokemonActivo();
  for (Movimiento &mov : movs) {
    if (nombre == mov.getNombre())
      return std::make_shared<Movimiento>(mov);
  }
  return nullptr;
}
