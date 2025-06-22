#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include "Validaciones.h"
#include "Fecha.h"

int Validaciones::ingresoDatos(const char* msj) { 
    char c;
    int valor, i = 0;
    char dato[10];
    printf("\n%s", msj);
    while (true) {
        c = getch();
        if (c == 13) break; // Enter
        if (c == 8) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (c >= '0' && c <= '9') {
            if (i < 9) {
                dato[i++] = c;
                printf("%c", c);
            }
        }
    }
    dato[i] = '\0';
    valor = atoi(dato);
    return valor;
}

int Validaciones::ingresoOpcionMenu(const char* msj) {
    char c;
    int valor, i = 0;
    char dato[10];
    printf("\n%s", msj);
    while (true) {
        c = getch();
        if (c == 13) break; // Enter
        if (c == 8) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (c >= '0' && c <= '9') {
            if (i < 9) {
                dato[i++] = c;
                printf("%c", c);
            }
        } else {
            printf("\nSolo se permiten numeros. Intente de nuevo.");
            return -1; // Indica entrada inválida
        }
    }
    dato[i] = '\0';
    valor = atoi(dato);
    return valor;
}

char Validaciones::ingresoCaracter(const char* msj) {
    char c;
    printf("\n%s", msj);
    while (true) {
        fflush(stdin); // si estás en Windows y usando conio.h
        c = getch();

        if (c == 8) { // Backspace
            printf("\b \b");
            continue;
        }
        if (c == 's' || c == 'S' || c == 'n' || c == 'N') {
            printf("%c\n", c);
            return c;
        } else {
            printf("\nEntrada invalida. Solo se permite 's' o 'n'. Intente de nuevo: ");
        }
    }
}

bool Validaciones::validarAnio(int anio) {
    const int MIN_ANIO = 1900;
    const int MAX_ANIO = 2025;
    if (anio < MIN_ANIO || anio > MAX_ANIO) {
        return false;
    }
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

// Implementación de la función solicitada
void Validaciones::siguienteFeriadoYDiaHabil(Fecha fecha, Fecha &feriado, Fecha &diaHabil) {
    // Buscar siguiente feriado
    feriado = fecha;
    do {
        // Avanzar un día
        int d = feriado.getDia();
        int m = feriado.getMes();
        int a = feriado.getAnio().getAnio();
        d++;
        // Ajustar mes y año si es necesario
        int diasMes;
        if (m == 2) {
            diasMes = (feriado.getAnio().getAnioBisiesto() ? 29 : 28);
        } else if (m == 4 || m == 6 || m == 9 || m == 11) {
            diasMes = 30;
        } else {
            diasMes = 31;
        }
        if (d > diasMes) {
            d = 1;
            m++;
            if (m > 12) {
                m = 1;
                a++;
            }
        }
        Anio nuevoAnio;
        nuevoAnio.setAnio(a);
        nuevoAnio.setAnioBisiesto(validarAnio(a));
        feriado.setAnio(nuevoAnio);
        feriado.setMes(m);
        feriado.setDia(d);
    } while (!feriado.esFeriadoEcuador());

    // Buscar siguiente día hábil después del feriado
    diaHabil = feriado;
    do {
        int d = diaHabil.getDia();
        int m = diaHabil.getMes();
        int a = diaHabil.getAnio().getAnio();
        d++;
        int diasMes;
        if (m == 2) {
            diasMes = (diaHabil.getAnio().getAnioBisiesto() ? 29 : 28);
        } else if (m == 4 || m == 6 || m == 9 || m == 11) {
            diasMes = 30;
        } else {
            diasMes = 31;
        }
        if (d > diasMes) {
            d = 1;
            m++;
            if (m > 12) {
                m = 1;
                a++;
            }
        }
        Anio nuevoAnio;
        nuevoAnio.setAnio(a);
        nuevoAnio.setAnioBisiesto(validarAnio(a));
        diaHabil.setAnio(nuevoAnio);
        diaHabil.setMes(m);
        diaHabil.setDia(d);
    } while (diaHabil.esFeriadoEcuador() || diaHabil.esFinDeSemana());
}

void Validaciones::mostrarSiguienteFeriadoYDiaHabil(Fecha fecha) {
    Fecha feriado, diaHabil;
    siguienteFeriadoYDiaHabil(fecha, feriado, diaHabil);
    printf("\nSiguiente feriado: %d/%d/%d", feriado.getDia(), feriado.getMes(), feriado.getAnio().getAnio());
    printf("\nSiguiente dia habil: %d/%d/%d", diaHabil.getDia(), diaHabil.getMes(), diaHabil.getAnio().getAnio());
}