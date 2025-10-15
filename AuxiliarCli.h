#ifndef AUXILIARCLI_H
#define AUXILIARCLI_H

#include <iostream>

class AuxiliarCli
{
private:
    void cambiarColorCli(std::string colorId);

public:
    AuxiliarCli();
    
    void imprimirLog(std::string nivel, std::string mensaje);
};

#endif