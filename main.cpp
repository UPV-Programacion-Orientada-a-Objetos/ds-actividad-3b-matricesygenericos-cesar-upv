#include <iostream>
#include <iomanip>
#include "MatrizDinamica.h"
#include "AuxiliarCli.h"

// * Imprimir una matriz genéric
template <typename T>
void imprimirMatriz(const MatrizDinamica<T> &matriz)
{
    // recorrer cada fila de la matriz
    for (int fila = 0; fila < matriz.getFilas(); ++fila)
    {
        std::cout << "| ";

        // recorrer cada columna de la fila actual
        for (int columna = 0; columna < matriz.getColumnas(); ++columna)
        {
            // imprimir el elemento con 2 decimales de precisión
            std::cout << std::fixed << std::setprecision(2) << matriz(fila, columna);

            // agregar separador entre columnas o espacio final
            if (columna < matriz.getColumnas() - 1)
                std::cout << " | ";
            else
                std::cout << " ";
        }

        std::cout << "|\n";
    }
}

int main()
{
    AuxiliarCli<int> cliInt;     // auxiliar para enteros
    AuxiliarCli<float> cliFloat; // auxiliar para flotantes

    cliInt.imprimirLog("STATUS", "--- Sistema de Análisis de Transformaciones Lineales ---");
    std::cout << "\n";

    // creación y entrada de la matriz 2x3
    cliInt.imprimirLog("STATUS", ">> Prueba de Matriz ENTERA (Matriz A) <<");
    cliInt.imprimirLog("STATUS", "Creando Matriz A (Tipo INT) de 2x3...");

    MatrizDinamica<int> matrizA(2, 3);

    // solicitar valores al usuario para llenar la matriz A
    cliInt.imprimirLog("STATUS", "Ingresar valores para A (2x3):");
    for (int fila = 0; fila < matrizA.getFilas(); ++fila)
    {
        for (int columna = 0; columna < matrizA.getColumnas(); ++columna)
        {
            int valorEntrada;
            std::string prompt = "A[" + std::to_string(fila) + "," + std::to_string(columna) + "]";
            cliInt.obtenerDato(prompt, valorEntrada);
            matrizA(fila, columna) = valorEntrada;
        }
    }
    std::cout << "\n";

    // redimensionar matriz A de 2x3 a 3x3
    cliInt.imprimirLog("STATUS", ">> Redimensionando Matriz A <<");
    cliInt.imprimirLog("STATUS", "Redimensionando A a 3x3. Datos conservados:");

    matrizA.redimensionarMatriz(3, 3);
    imprimirMatriz(matrizA);
    std::cout << "\n";

    // crear matriz B de floats
    cliInt.imprimirLog("STATUS", ">> Prueba de Multiplicación (Tipo FLOAT) <<");
    cliInt.imprimirLog("STATUS", "Creando Matriz B (Tipo FLOAT) de 3x2...");

    MatrizDinamica<float> matrizB(3, 2);

    // solicitar valores al usuario para llenar la matriz B
    for (int fila = 0; fila < matrizB.getFilas(); ++fila)
    {
        for (int columna = 0; columna < matrizB.getColumnas(); ++columna)
        {
            float valorEntrada;
            std::string prompt = "B[" + std::to_string(fila) + "," + std::to_string(columna) + "]";
            cliFloat.obtenerDato(prompt, valorEntrada);
            matrizB(fila, columna) = valorEntrada;
        }
    }
    std::cout << "\n";

    // convertir de int a float para multiplicar
    // crear matriz AF (float) con las mismas dimensiones que A
    MatrizDinamica<float> matrizAFloat(matrizA.getFilas(), matrizA.getColumnas());

    // copiar y convertir cada elemento de A (int) a AF (float)
    for (int fila = 0; fila < matrizA.getFilas(); ++fila)
    {
        for (int columna = 0; columna < matrizA.getColumnas(); ++columna)
        {
            matrizAFloat(fila, columna) = static_cast<float>(matrizA(fila, columna));
        }
    }

    
    // multiplicar matrices
    cliInt.imprimirLog("STATUS", "Calculando C = A(3x3) x B(3x2) ...");

    MatrizDinamica<float> matrizC = MatrizDinamica<float>::multiplicar(matrizAFloat, matrizB);

    // verificar si la multiplicación fue exitosa
    if (matrizC.getFilas() == 0 || matrizC.getColumnas() == 0)
    {
        cliInt.imprimirLog("WARNING", "No se pudo calcular C por dimensiones incompatibles.");
    }
    else
    {
        cliInt.imprimirLog("SUCCESS", "Matriz C (Resultado 3x2, Tipo FLOAT):");
        imprimirMatriz(matrizC);
    }
    std::cout << "\n";

    // fin
    cliInt.imprimirLog("STATUS", "Liberando memoria de todas las matrices...");
    // aqui se ejecutan los destructores
    return 0;
}