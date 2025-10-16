#include "AuxiliarCli.h"

// * Estilizar logs usando colores ANSI
template <typename T>
void AuxiliarCli<T>::cambiarColorCli(std::string color)
{
    int code = 0;

    if (color == "RED" || color == "red")
        code = 31;
    if (color == "GREEN" || color == "green")
        code = 32;
    if (color == "YELLOW" || color == "yellow")
        code = 33;
    if (color == "WHITE" || color == "white")
        code = 37;
    if (color == "CYAN" || color == "cyan")
        code = 36;

    std::cout << "\033[" << code << "m";
}

// * Imprimir logs para debug
template <typename T>
void AuxiliarCli<T>::imprimirLog(std::string tipo, std::string msj)
{
    std::string color = "WHITE";
    if (tipo == "WARNING" || tipo == "warning")
        color = "YELLOW";
    else if (tipo == "STATUS" || tipo == "status")
        color = "CYAN";
    else if (tipo == "SUCCESS" || tipo == "success")
        color = "GREEN";
    else if (tipo == "ERROR" || tipo == "error")
        color = "RED";

    cambiarColorCli(color);
    std::cout << "[" << tipo << "] " << msj << std::endl;
    std::cout << "\033[0m";
}

// * Obtener tipos de datos primitivos (sin strings ni booleanos)
template <typename T>
void AuxiliarCli<T>::obtenerDato(std::string mensaje, T &valor)
{
    mensaje += ": ";
    std::cout << mensaje;

    while (!(std::cin >> valor))
    {
        imprimirLog("WARNING", "Entrada no válida, por favor, intente de nuevo.");
        std::cin.clear();                                                   // limpiar el error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar el línea

        std::cout << std::endl
                  << mensaje;
    }

    // limpiar buffer de vuelta, ya que se pudo haber escrito algo más
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// * Instanciaciones explicitas
template class AuxiliarCli<int>;
template class AuxiliarCli<float>;
template class AuxiliarCli<double>;
