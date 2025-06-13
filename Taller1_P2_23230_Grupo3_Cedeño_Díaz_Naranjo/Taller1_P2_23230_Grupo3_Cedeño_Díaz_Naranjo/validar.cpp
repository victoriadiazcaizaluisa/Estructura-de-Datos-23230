#include "validar.h"
#include <iostream>
#include <cstring>
#include <conio.h>

using namespace std;

char* Validar::pedirNombre() {
    char* nombre = new char[100]; // Asignar memoria para el nombre
    int i;
    char c;

    do {
        i = 0;
        cout << "Ingrese su nombre: ";
        while (true) {
            c = _getch();
            if (c == 13) { // Enter
                cout << endl;
                break;
            } else if (c == 8) { // Backspace
                if (i > 0) {
                    i--;
                    cout << "\b \b";
                }
            } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                nombre[i++] = c;
                cout << c;
            }
        }

        if (i == 0) {
            cout << "El nombre no puede estar vacio. Intente de nuevo." << endl;
        }

    } while (i == 0);

    nombre[i] = '\0'; // Fin de cadena
    return nombre;
}
