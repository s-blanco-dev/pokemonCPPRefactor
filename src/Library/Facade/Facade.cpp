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
  std::string mensaje;
  
 Entrenador ent1 = listaEspera[0]; 
 Entrenador ent2 = listaEspera[1]; 

 batallaActual = new Batalla(ent1, ent2, gen);
 mensaje = batallaActual->iniciarBatalla();

 return mensaje;
}

std::string Facade::seleccionarPokemon(std::string nombrePok, std::string nombreEnt) {
    Entrenador* ente = buscarEntrenadorPorNombre(nombreEnt);
    Pokemon* pokemon = pokedexActual->getPokemonByName(nombrePok);

    if (pokemon == nullptr) {
        return "El pokemon no está disponible";
    }

    // Pasar punteros directamente a Batalla
    return batallaActual->seleccionarPokemon(*ente, *pokemon);
}

std::string Facade::atacar(std::string nombreEnt, Movimiento movimiento) {
  Entrenador* ente = buscarEntrenadorPorNombre(nombreEnt);
  // A terminar
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
