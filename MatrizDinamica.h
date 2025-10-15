#ifndef MATRIZDINAMICA_H
#define MATRIZDINAMICA_H

template <typename T>
class MatrizDinamica
{
private:
    T **datos;
    int filas;
    int columnas;

public:
    // * Constructor
    MatrizDinamica(int f, int c);

    // * Destructor
    ~MatrizDinamica();

    // * Redimensión dinámica
    redimensionarMatriz(int nuevaF, int nuevaC);
};

#endif