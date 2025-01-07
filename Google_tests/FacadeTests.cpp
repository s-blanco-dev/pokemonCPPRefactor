//
// Created by jwillmore on 12/15/24.
//

#include "../src/Library/Facade/Facade.h"
#include "../src/Library/Generador/GeneradorFijo.h"
#include "../src/Library/Logica/Entrenador.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <exception>
#include <stdexcept>

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

  auto inventarioItems = ernesto->getItems();
  int usosAntesDeAtacar = inventarioItems[0]->getUsos();

  int hpAnterior = ernesto->getPokemonActivo()
                       ->getHP(); // Ley de Demeter violada satisfactoriamente
  facade->usarItem("Ernesto", "SuperPocion");

  int usosDespuesDeAtacar = inventarioItems[0]->getUsos();
  int hpNueva = ernesto->getPokemonActivo()
                    ->getHP(); // Ley de Demeter violada satisfactoriamente
  ASSERT_GT(hpNueva, hpAnterior);
  ASSERT_LT(usosDespuesDeAtacar, usosAntesDeAtacar);
}

TEST(FacadeTest, ItemSinPiola) {
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

  auto inventarioItems = ernesto->getItems();
  inventarioItems[0]->setUsos(0);

  ASSERT_EQ(facade->usarItem("Ernesto", "SuperPocion"),
            "Se te terminó la piola, muchacho.");
}

// Punto de entrada para Google Test
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
