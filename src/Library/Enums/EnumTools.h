#ifndef ENUMTOOLS_H
#define ENUMTOOLS_H
#include "EEstado.h"
#include "ETipos.h"
#include <string>

class EnumTools {
public:
  static std::string estadoToString(EEstado estado);
  static std::string tipoToString(ETipos tipo);
};

#endif // !EnumTools
