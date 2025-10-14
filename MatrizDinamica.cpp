#include <iostream>
#include "MatrizDinamica.h"

// * Constructor
template <typename T>
MatrizDinamica<T>::MatrizDinamica(int f, int c) : filas(f), columnas(c) {
    // i. Crear los arreglos de filas y columnas
    datos = new T* [filas]{};
    for (size_t i = 0; i < filas; i++) {
        datos[i] = new T [columnas]{};
    }
}

// * Destructor
template <typename T>
MatrizDinamica<T>::~MatrizDinamica() {
    // i. Liberar las columnas
    for (size_t i = 0; i < filas; i++) {
        delete[] datos[i];
    }

    // ii. Liberar el puntero hacia las filas
    delete[] datos;
}