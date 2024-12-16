project(Google_tests)

# Agregar directorio de Google Test
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Incluir los directorios del proyecto principal
include_directories(${CMAKE_SOURCE_DIR}/src)

# Agregar los archivos fuente del proyecto principal, excluyendo main.cpp
file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*main\\.cpp$") # Excluye main.cpp

# Crear ejecutable de pruebas
add_executable(Google_Tests_run FacadeTests.cpp BatallaTests.cpp ${PROJECT_SOURCES})
target_link_libraries(Google_Tests_run gtest gtest_main)

# Vincular la biblioteca DPP
find_package(DPP REQUIRED) # Asegúrate de que DPP tenga un archivo CMake de configuración
target_link_libraries(Google_Tests_run dpp)
