#include "../src/Library/Contenedores/Pokedex.h"
#include "../src/Library/Generador/GeneradorFijo.h"
#include "../src/Library/Logica/Batalla.h"
#include "../src/Library/Logica/Entrenador.h"
#include "../src/Library/Logica/Movimiento.h"
#include "../src/Library/Logica/Pokemon.h"
#include "../src/Library/Movimientos/Agua/Hidropulso.h"
#include "../src/Library/Movimientos/Electrico/Rayo.h"
#include "../src/Library/Movimientos/Fuego/Lanzallamas.h"
#include "../src/Library/Pokemons/Charizard.h"
#include "../src/Library/Pokemons/Pikachu.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <memory>

// Prueba para iniciarBatalla
TEST(BatallaTest, IniciarBatalla) {
  // Crear los entrenadores y la batalla
  Pokedex::resetInstance();
  auto entrenador1 = std::make_shared<Entrenador>("Ash");
  auto entrenador2 = std::make_shared<Entrenador>("Gary");

  auto pikachu = std::make_shared<Pokemon>(Pikachu());
  auto charizard = std::make_shared<Pokemon>(Charizard());

  GeneradorFijo generador = GeneradorFijo();
  Batalla batalla(entrenador1, entrenador2, &generador);

  entrenador1->agregarPokemon(pikachu);
  entrenador2->agregarPokemon(charizard);

  // Ejecutar el test
  std::string resultado = batalla.iniciarBatalla();

  // Comprobar que el mensaje contiene "ha empezado la batalla!"
  ASSERT_NE(resultado.find("ha empezado la batalla!"), std::string::npos);
  ASSERT_NO_THROW(batalla.esTurnoDe(entrenador1));
}

// Prueba para atacar (ataque válido)
TEST(BatallaTest, Atacar_Exitoso) {
  // Crear los entrenadores y la batalla
  Pokedex::resetInstance();
  auto entrenador1 = std::make_shared<Entrenador>("Ash");
  auto entrenador2 = std::make_shared<Entrenador>("Gary");

  auto pikachu = std::make_shared<Pokemon>(Pikachu());
  auto charizard = std::make_shared<Pokemon>(Charizard());

  GeneradorFijo generador = GeneradorFijo();
  Batalla batalla(entrenador1, entrenador2, &generador);

  entrenador1->agregarPokemon(pikachu);
  entrenador2->agregarPokemon(charizard);

  entrenador1->setPokemonActivo(pikachu);
  entrenador2->setPokemonActivo(charizard);

  // Ejecutar el test
  Movimiento ataque = Rayo();
  std::string resultado = batalla.atacar(entrenador1, ataque);

  // Verificar que el ataque fue exitoso y el PP se redujo
  ASSERT_THAT(resultado, testing::HasSubstr("Rayo"));
  ASSERT_EQ(ataque.getCurrentPP(), ataque.getPP() - 1);
}

TEST(BatallaTest, MovimientoNoPresente) {
  // Crear los entrenadores y la batalla
  Pokedex::resetInstance();
  auto entrenador1 = std::make_shared<Entrenador>("Ash");
  auto entrenador2 = std::make_shared<Entrenador>("Gary");

  auto pikachu = std::make_shared<Pokemon>(Pikachu());
  auto charizard = std::make_shared<Pokemon>(Charizard());

  GeneradorFijo generador = GeneradorFijo();
  Batalla batalla(entrenador1, entrenador2, &generador);

  entrenador1->agregarPokemon(pikachu);
  entrenador2->agregarPokemon(charizard);

  entrenador1->setPokemonActivo(pikachu);
  entrenador2->setPokemonActivo(charizard);

  // Ejecutar el test
  Movimiento ataque = Lanzallamas();
  std::string resultado = batalla.atacar(entrenador1, ataque);

  // Verificar que el ataque fue exitoso y el PP se redujo
  ASSERT_THAT(resultado, testing::HasSubstr("no está presente"));
}

// Prueba para atacar fuera de turno
TEST(BatallaTest, Atacar_FueraDeTurno) {
  // Crear los entrenadores y la batalla
  Pokedex::resetInstance();
  auto entrenador1 = std::make_shared<Entrenador>("Ash");
  auto entrenador2 = std::make_shared<Entrenador>("Gary");

  auto pikachu = std::make_shared<Pokemon>(Pikachu());
  auto charizard = std::make_shared<Pokemon>(Charizard());

  GeneradorFijo generador = GeneradorFijo();
  Batalla batalla(entrenador1, entrenador2, &generador);

  entrenador1->agregarPokemon(pikachu);
  entrenador2->agregarPokemon(charizard);
  entrenador1->setPokemonActivo(pikachu);
  entrenador2->setPokemonActivo(charizard);

  // Ejecutar el test
  Movimiento ataque = Lanzallamas();
  std::string resultado = batalla.atacar(entrenador2, ataque);

  // Verificar que el ataque fue fuera de turno
  ASSERT_EQ(resultado, "No es tu turno, Gary!");
}

// Prueba para seleccionarPokemon (válido)
TEST(BatallaTest, SeleccionarPokemon_Exitoso) {
  // Crear los entrenadores y la batalla
  Pokedex::resetInstance();
  auto entrenador1 = std::make_shared<Entrenador>("Ash");
  auto entrenador2 = std::make_shared<Entrenador>("Gary");

  auto pikachu = std::make_shared<Pokemon>(Pikachu());
  auto charizard = std::make_shared<Pokemon>(Charizard());

  GeneradorFijo generador = GeneradorFijo();
  Batalla batalla(entrenador1, entrenador2, &generador);

  Pokedex *pokedex = Pokedex::getInstance();

  // Ejecutar el test
  std::string resultado = batalla.seleccionarPokemon(
      entrenador1, *pokedex->getPokemonByName("Pikachu"));

  // Verificar que el pokemon fue seleccionado correctamente
  ASSERT_NE(resultado.find("ha seleccionado a **Pikachu**"), std::string::npos);
  ASSERT_EQ(entrenador1->getPokemonActivo()->getNombre(), "Pikachu");
}

// Prueba para verificar estados del Pokémon
TEST(BatallaTest, VerificarEstadoPokemon) {
  // Crear los entrenadores y la batalla
  Pokedex::resetInstance();
  auto entrenador1 = std::make_shared<Entrenador>("Ash");
  auto entrenador2 = std::make_shared<Entrenador>("Gary");

  auto pikachu = std::make_shared<Pokemon>(Pikachu());
  auto charizard = std::make_shared<Pokemon>(Charizard());

  GeneradorFijo generador = GeneradorFijo();
  Batalla batalla(entrenador1, entrenador2, &generador);

  entrenador1->agregarPokemon(pikachu);
  entrenador2->agregarPokemon(charizard);
  entrenador1->setPokemonActivo(pikachu);
  entrenador2->setPokemonActivo(charizard);

  // Establecer el estado del pokemon
  entrenador1->getPokemonActivo()->setTurnosDormido(2);
  Movimiento ataque = Rayo();
  std::string resultado = batalla.atacar(entrenador1, ataque);

  ASSERT_THAT(resultado, testing::HasSubstr("Dormido** y no puede atacar"));
}

TEST(BatallaTest, ataqueAplicaEfecto) {

  Pokedex::resetInstance();
  auto entrenador1 = std::make_shared<Entrenador>("Ash");
  auto entrenador2 = std::make_shared<Entrenador>("Gary");

  auto pikachu = std::make_shared<Pokemon>(Pikachu());
  auto charizard = std::make_shared<Pokemon>(Charizard());

  GeneradorFijo generador = GeneradorFijo();
  Batalla batalla(entrenador1, entrenador2, &generador);

  entrenador1->agregarPokemon(pikachu);
  entrenador2->agregarPokemon(charizard);
  entrenador1->setPokemonActivo(pikachu);
  entrenador2->setPokemonActivo(charizard);

  Movimiento paralizador = Rayo();
  batalla.atacar(entrenador1, paralizador);

  ASSERT_EQ(charizard->getEstado(), EEstado::PARALIZADO);
}

TEST(BatallaTest, cambiarPokemonExitoso) {
  Pokedex::resetInstance();
  auto entrenador1 = std::make_shared<Entrenador>("Ash");
  auto entrenador2 = std::make_shared<Entrenador>("Gary");

  auto pikachu = std::make_shared<Pokemon>(Pikachu());
  auto charizard = std::make_shared<Pokemon>(Charizard());

  GeneradorFijo generador = GeneradorFijo();
  Batalla batalla(entrenador1, entrenador2, &generador);

  entrenador1->agregarPokemon(pikachu);
  entrenador1->agregarPokemon(charizard);
  entrenador1->setPokemonActivo(pikachu);

  batalla.cambiarPokemonActivo(entrenador1, charizard);

  ASSERT_EQ(entrenador1->getPokemonActivo()->getNombre(), "Charizard");
}
