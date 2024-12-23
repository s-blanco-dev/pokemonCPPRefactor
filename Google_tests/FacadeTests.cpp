//
// Created by jwillmore on 12/15/24.
//

#include "../src/Library/Facade/Facade.h"
#include "../src/Library/Generador/GeneradorFijo.h"
#include "../src/Library/Logica/Entrenador.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

// Verificar que retorne un mensaje con el nombre del entrenador
TEST(FacadeTest, unirBatalla) {
  EXPECT_THAT(Facade::getInstance()->unirBatalla("Hugo"),
              testing::HasSubstr("Hugo"));
}

TEST(FacadeTest, usarItem) {
  Facade::resetInstance();
  Facade *facade = Facade::getInstance();
  facade->unirBatalla("Chorro");
  facade->unirBatalla("Ernesto");

  GeneradorFijo gen = GeneradorFijo();
  facade->iniciarBatalla(&gen);

  Batalla *bataActual = facade->getBatalla();
  auto chorro = bataActual->obtenerEntrenadorPorNombre("Chorro");
  auto ernesto = bataActual->obtenerEntrenadorPorNombre("Ernesto");

  facade->seleccionarPokemon("Pikachu", "Chorro");
  facade->seleccionarPokemon("Charizard", "Ernesto");
  facade->atacar("Chorro", "Rayo");

  int hpAnterior = ernesto->getPokemonActivo()
                       ->getHP(); // Ley de Demeter violada satisfactoriamente
  facade->usarItem("Ernesto", "SuperPocion");
  int hpNueva = ernesto->getPokemonActivo()
                    ->getHP(); // Ley de Demeter violada satisfactoriamente
  ASSERT_GT(hpNueva, hpAnterior);
}
// Punto de entrada para Google Test
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
