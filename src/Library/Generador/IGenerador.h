//
// Created by jwillmore on 12/6/24.
//

#ifndef IGENERADOR_H
#define IGENERADOR_H



class IGenerador {
    public:

    virtual ~IGenerador();
    virtual int generarNum(int num) const = 0;

};



#endif //IGENERADOR_H
