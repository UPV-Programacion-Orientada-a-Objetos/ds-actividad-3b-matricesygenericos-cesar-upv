#ifndef MATRIZDINAMICA_H
#define MATRIZDINAMICA_H

#include <string>
#include <stdexcept>
#include <utility>
#include "AuxiliarCli.h"

template <typename T>
class MatrizDinamica
{
private:
    T **datos;
    int filas;
    int columnas;
    AuxiliarCli<T> cli;

    // * Reservar memoria para una matriz de tamaño n x m
    void reservar(int f, int c)
    {
        if (f < 0 || c < 0)
        {
            cli.imprimirLog("WARNING", "Dimensiones negativas no permitidas (" + std::to_string(f) + "," + std::to_string(c) + ")");
            filas = 0;
            columnas = 0;
            datos = nullptr;
            return;
        }

        // asignar punteros a filas
        filas = f;
        columnas = c;
        datos = nullptr;

        if (filas == 0 || columnas == 0)
        {
            return;
        }

        // i. Crear los arreglos de filas y columnas
        try
        {
            // crear vector de punteros a filas
            datos = new T *[filas]{};
            for (int i = 0; i < filas; ++i)
            {
                // crear columnas e inicializar a T{}
                datos[i] = new T[columnas]{};
            }
        }
        catch (const std::bad_alloc &)
        {
            cli.imprimirLog("WARNING", "No hay memoria suficiente para reservar matriz de " + std::to_string(filas) + "x" + std::to_string(columnas));

            // limpiar
            if (datos)
            {
                for (int i = 0; i < filas; ++i)
                {
                    delete[] datos[i];
                }
                delete[] datos;
            }
            datos = nullptr;
            filas = 0;
            columnas = 0;
        }
    }

    // * Liberar toda la memoria asociada a la matriz
    void liberar()
    {
        // liberar columnas
        if (datos)
        {
            for (int i = 0; i < filas; ++i)
            {
                delete[] datos[i];
            }
            // liberar puntero de filas
            delete[] datos;
        }
        datos = nullptr;
        filas = 0;
        columnas = 0;
    }

public:
    // * Constructor: reserva memoria para las matrices
    MatrizDinamica(int f, int c) : datos(nullptr), filas(0), columnas(0)
    {
        // reservar memoria e inicializar
        cli.imprimirLog("STATUS", "Creando Matriz (" + std::to_string(f) + "x" + std::to_string(c) + ")");

        reservar(f, c);
    }

    // * Destructor: libera la memoria
    ~MatrizDinamica()
    {
        liberar();
    }

    // * Constructor de copia: duplica el contenido de otra matriz
    MatrizDinamica(const MatrizDinamica &otra) : datos(nullptr), filas(0), columnas(0)
    {
        // reservar mismo tamaño
        AuxiliarCli<T> cli;
        cli.imprimirLog("STATUS", "Matriz reservada (" + std::to_string(filas) + "x" + std::to_string(columnas) + ")");

        reservar(otra.filas, otra.columnas);
        // copiar datos celda por celda
        for (int i = 0; i < filas; ++i)
            for (int j = 0; j < columnas; ++j)
                datos[i][j] = otra.datos[i][j];
    }

    // * Asignación por copia: libera/duplica recursos
    MatrizDinamica &operator=(const MatrizDinamica &otra)
    {
        // evitar el mismo
        if (this == &otra)
            return *this;

        // si el tamaño es diferente, realocar
        if (filas != otra.filas || columnas != otra.columnas)
        {
            // liberar y reservar nuevo tamaño
            liberar();
            reservar(otra.filas, otra.columnas);
        }
        // copiar datos
        for (int i = 0; i < filas; ++i)
            for (int j = 0; j < columnas; ++j)
                datos[i][j] = otra.datos[i][j];

        return *this;
    }

    // * Constructor de movimiento: toma los recursos de otra matriz
    MatrizDinamica(MatrizDinamica &&otra) noexcept : datos(otra.datos), filas(otra.filas), columnas(otra.columnas)
    {
        // anular la fuente para evitar liberar dos veces
        otra.datos = nullptr;
        otra.filas = 0;
        otra.columnas = 0;
    }

    // * Asignación por movimiento: libera y toma los recursos de otra matriz
    MatrizDinamica &operator=(MatrizDinamica &&otra) noexcept
    {
        // evitar el mismo
        if (this == &otra)
            return *this;

        // liberar recursos actuales
        liberar();

        // mover recursos
        datos = otra.datos;
        filas = otra.filas;
        columnas = otra.columnas;

        // anular la fuente
        otra.datos = nullptr;
        otra.filas = 0;
        otra.columnas = 0;

        return *this;
    }

    // * Acceso mutable a un elemento
    T &at(int i, int j)
    {
        return datos[i][j];
    }

    // * Acceso de solo lectura a un elemento
    const T &at(int i, int j) const
    {
        return datos[i][j];
    }

    // * Operador () para acceso estilo A(i,j)
    T &operator()(int i, int j) { return at(i, j); }
    const T &operator()(int i, int j) const { return at(i, j); }

    // * Getter número de filas
    int getFilas() const { return filas; }

    // * Getter número de columnas
    int getColumnas() const { return columnas; }

    // * Redimensión dinámica: crea nueva matriz
    void redimensionarMatriz(int nuevaF, int nuevaC)
    {
        // si son negativas, ignorar
        if (nuevaF < 0 || nuevaC < 0)
        {
            cli.imprimirLog("WARNING", "Redimensión inválida: dimensiones negativas (" + std::to_string(nuevaF) + "," + std::to_string(nuevaC) + ")");
            return;
        }

        // si no cambia, no hacer nada
        if (nuevaF == filas && nuevaC == columnas)
            return;

        // log de inicio de redimensión
        cli.imprimirLog("STATUS", "Redimensionando de " + std::to_string(filas) + "x" + std::to_string(columnas) + " a " + std::to_string(nuevaF) + "x" + std::to_string(nuevaC));

        // crear matriz temporal con nuevas dimensiones
        try
        {

            cli.imprimirLog("STATUS", "Creando Matriz Temporal (" + std::to_string(nuevaF) + "x" + std::to_string(nuevaC) + ")");

            MatrizDinamica<T> temp(nuevaF, nuevaC);

            // copiar la intersección de datos existente
            const int minF = (nuevaF < filas) ? nuevaF : filas;
            const int minC = (nuevaC < columnas) ? nuevaC : columnas;
            for (int i = 0; i < minF; ++i)
                for (int j = 0; j < minC; ++j)
                    temp.datos[i][j] = datos[i][j];

            // mover temp a this
            *this = std::move(temp);
        }
        catch (...)
        {
            cli.imprimirLog("WARNING", "Falló la redimensión por falta de memoria");
            return;
        }

        cli.imprimirLog("SUCCESS", "Redimensión completada a (" + std::to_string(filas) + "x" + std::to_string(columnas) + ")");
    }

    // * Multiplicación
    static MatrizDinamica<T> multiplicar(const MatrizDinamica<T> &A, const MatrizDinamica<T> &B)
    {
        AuxiliarCli<T> cli;

        // validar compatibilidad
        if (A.getColumnas() != B.getFilas())
        {
            cli.imprimirLog("WARNING", "Dimensiones incompatibles para multiplicación: " + std::to_string(A.getFilas()) + "x" + std::to_string(A.getColumnas()) + " vs " + std::to_string(B.getFilas()) + "x" + std::to_string(B.getColumnas()));
            return MatrizDinamica<T>(0, 0);
        }

        // inicio de multiplicación
        cli.imprimirLog("STATUS", "Multiplicando (" + std::to_string(A.getFilas()) + "x" + std::to_string(A.getColumnas()) + ") x (" + std::to_string(B.getFilas()) + "x" + std::to_string(B.getColumnas()) + ")");

        // crear resultado
        MatrizDinamica<T> C(A.getFilas(), B.getColumnas());

        // multiplicación estándar
        for (int i = 0; i < A.getFilas(); ++i)
        {
            for (int j = 0; j < B.getColumnas(); ++j)
            {
                T suma{}; // acumulador
                for (int k = 0; k < A.getColumnas(); ++k)
                {
                    suma += A(i, k) * B(k, j);
                }
                C(i, j) = suma;
            }
        }

        cli.imprimirLog("SUCCESS", "Multiplicación completada");

        return C;
    }
};

#endif