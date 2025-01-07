//
// Created by jwillmore on 12/5/24.
//

#ifndef IITEM_H
#define IITEM_H
#include <string>

#include "../Logica/Pokemon.h"
using namespace std;

class IItem {
public:
  virtual ~IItem() = default; // DESTRUCTOR

  virtual string getNombre() const = 0;
  virtual string getDescripcion() const = 0;
  virtual int getUsos() const = 0;
  virtual int getUsosMax() const = 0;
  virtual void setUsos(int usos) = 0;

  virtual void usarIItem(Pokemon &pokemon) = 0;
};

#endif // IITEM_H
