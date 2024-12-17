#include "EnumTools.h"
#include "EEstado.h"
#include "ETipos.h"
#include <string>

std::string EnumTools::tipoToString(ETipos tipo) {
  switch (tipo) {
  case ETipos::FUEGO:
    return "Fuego";
  case ETipos::PLANTA:
    return "Planta";
  case ETipos::AGUA:
    return "Agua";
  case ETipos::PSIQUICO:
    return "Psiquo";
  case ETipos::ELECTRICO:
    return "Electrico";
  case ETipos::BICHO:
    return "Bicho";
  case ETipos::HADA:
    return "Hada";
  case ETipos::VENENO:
    return "Veneno";
  case ETipos::NORMAL:
    return "Normal";
  case ETipos::ROCA:
    return "Roca";
  case ETipos::TIERRA:
    return "Tierra";
  case ETipos::HIELO:
    return "Hilo";
  case ETipos::SINIESTRO:
    return "Sinistro";
  case ETipos::FANTASMA:
    return "Fantasma";
  case ETipos::LUCHA:
    return "Lucha";
  case ETipos::DRAGON:
    return "Dragon";
  case ETipos::ACERO:
    return "Acero";
  case ETipos::VOLADOR:
    return "Volador";
  default:
    return "Desconocido";
  }
}

std::string EnumTools::estadoToString(EEstado estado) {
  switch (estado) {
  case EEstado::NORMAL:
    return ":white_check_mark:Normal";
  case EEstado::DORMIDO:
    return ":zzz:Dormido";
  case EEstado::QUEMADO:
    return ":fire:Quemado";
  case EEstado::ENVENENADO:
    return ":test_tube:Envenado";
  case EEstado::PARALIZADO:
    return ":link:Paralizado";
  default:
    return "Desconocido";
  }
}
