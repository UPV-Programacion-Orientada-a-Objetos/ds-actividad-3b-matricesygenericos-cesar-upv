#ifndef AUXILIARCLI_H
#define AUXILIARCLI_H

#include <iostream>
#include <string>
#include <limits>

template <typename T>
class AuxiliarCli
{
public:
    AuxiliarCli() = default;

    // * Imprimir logs para debug
    void imprimirLog(std::string tipo, std::string msj);

    // * Obtener tipos de datos primitivos (sin strings ni booleanos)
    void obtenerDato(std::string mensaje, T &valor);

private:
    // * Estilizar logs usando colores ANSI
    void cambiarColorCli(std::string color);
};

#endif