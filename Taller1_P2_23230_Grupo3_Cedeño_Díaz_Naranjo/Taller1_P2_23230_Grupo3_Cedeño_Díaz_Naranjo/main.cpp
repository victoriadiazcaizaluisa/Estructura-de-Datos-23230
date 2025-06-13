#include <iostream>
#include <cstring>
#include <conio.h>
#include "shellSort.cpp"
#include "validar.cpp"

int main() {
    bool repetir = true;
    while (repetir) {
        char* entrada = Validar::pedirNombre();
        int longitud = std::strlen(entrada);

        ShellSort ordenador;

        ordenador.convertirAMinusculas(entrada, longitud);
        ordenador.ordenarCaracteres(entrada, longitud);

        std::cout << "Nombre ordenado alfabeticamente (ignorando mayusculas): " << entrada << std::endl;

        delete[] entrada;
                
        while (true) {
            std::cout << "Desea realizar otra operacion (s/n): ";
            char opcion = _getch();
            std::cout << opcion << std::endl;
            if (opcion == 's' || opcion == 'S') {
                repetir = true;
                break;
            } else if (opcion == 'n' || opcion == 'N') {
                std::cout << "Saliendo del programa." << std::endl;
                repetir = false;
                break;
            } else {
                std::cout << "Opcion no valida. Solo puede ingresar 's', 'S', 'n' o 'N'." << std::endl;
            }
        }
    }
    return 0;
}