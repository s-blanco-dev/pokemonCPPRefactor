//
// Created by jwillmore on 12/15/24.
//

#include "../src/Library/Facade/Facade.h"
#include "../src/Library/Logica/Entrenador.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

// Verificar que retorne un mensaje con el nombre del entrenador
TEST(FacadeTest, unirBatalla) {
  EXPECT_THAT(Facade::getInstance()->unirBatalla("Hugo"),
              testing::HasSubstr("Hugo"));
}

// Punto de entrada para Google Test
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
