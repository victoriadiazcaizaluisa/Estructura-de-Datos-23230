#include "shellSort.h"
#include <cctype> // para tolower

void ShellSort::convertirAMinusculas(char* arreglo, int longitud) {
    for (int i = 0; i < longitud; ++i) {
        arreglo[i] = std::tolower(arreglo[i]);
    }
}

void ShellSort::ordenarCaracteres(char* arreglo, int longitud) {
    int salto = longitud / 2;

    while (salto > 0) {
        for (int i = salto; i < longitud; i++) {
            int j = i - salto;
            while (j >= 0) {
                int k = j + salto;
                if (arreglo[j] <= arreglo[k]) {
                    j = -1;
                } else {
                    char temp = arreglo[j];
                    arreglo[j] = arreglo[k];
                    arreglo[k] = temp;
                    j = j - salto;
                }
            }
        }
        salto /= 2;
    }
}
