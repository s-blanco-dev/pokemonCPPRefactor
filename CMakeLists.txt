cmake_minimum_required(VERSION 3.30)
project(pokemonCppRefactor)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(libs/DPP)

add_executable(pokemonCppRefactor src/Library/main.cpp
        src/Library/Logica/Pokemon.cpp
        src/Library/Logica/Pokemon.h
        src/Library/Pokemons/Pikachu.cpp
        src/Library/Enums/ETipos.h
        src/Library/Logica/Movimiento.cpp
        src/Library/Logica/Movimiento.h
        src/Library/Enums/EEstado.h
        src/Library/Movimientos/Fuego/Lanzallamas.cpp
        src/Library/Pokemons/Pikachu.h
        src/Library/Movimientos/Fuego/Lanzallamas.h
        src/Library/Pokemons/Charizard.cpp
        src/Library/Pokemons/Charizard.h
        src/Library/Logica/Entrenador.cpp
        src/Library/Logica/Entrenador.h
        src/Library/Interfaces/IItem.h
        src/Library/Items/SuperPocion.cpp
        src/Library/Items/SuperPocion.h
        src/Library/Logica/Batalla.cpp
        src/Library/Logica/Batalla.h
        src/Library/Contenedores/Pokedex.cpp
        src/Library/Contenedores/Pokedex.h
        src/Library/Generador/IGenerador.h
        src/Library/Generador/GeneradorContexto.cpp
        src/Library/Generador/GeneradorContexto.h
        src/Library/Generador/GeneradorAleatorio.cpp
        src/Library/Generador/GeneradorAleatorio.h
        src/Library/Generador/GeneradorFijo.cpp
        src/Library/Generador/GeneradorFijo.h
        src/Library/Generador/IGenerador.cpp
        src/Library/Logica/LogicaAtaque.cpp
        src/Library/Logica/LogicaAtaque.h
        src/Library/Bot/bot.cpp
        src/Library/Facade/Facade.cpp
        src/Library/Facade/Facade.h
        src/Library/Facade/Menu.cpp
        src/Library/Facade/Menu.h
        src/Library/Contenedores/Efectividad.cpp
        src/Library/Contenedores/Efectividad.h
)

# Linking libraries
target_link_libraries(${PROJECT_NAME}
        dpp
)
# Specify includes
target_include_directories(${PROJECT_NAME} PRIVATE
        libs/DPP/include
)

# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20 # or 20 if you want something more recent
        CXX_STANDARD_REQUIRED ON
)