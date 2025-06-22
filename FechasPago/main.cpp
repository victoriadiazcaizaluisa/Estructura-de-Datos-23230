/**************************************************************************************************************
 Nombnre: Victoria Díaz
 Asignatura: Estructura de Datos
 Nrc: 23230
 Fecha: 30/04/2025
 ********************************************************************************************************/
#include "Anio.cpp"
#include "Fecha.cpp"
#include "Validaciones.cpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>

void pedirFecha(Fecha &fecha);
Validaciones objValidacion;

void mostrarMenu() {
    printf("\nMenu:");
    printf("\n1. Ingresar fecha");
    printf("\n2. Siguiente feriado y dia habil");
    printf("\n3. Salir");
    printf("\nSeleccione una opcion: ");
}

int main(int argc, char** argv) {
    int opcion;
    do {
        mostrarMenu();
        do {
            opcion = objValidacion.ingresoOpcionMenu("");
        } while (opcion == -1); // Repetir hasta que la entrada sea válida
        switch (opcion) {
            case 1: {
                Fecha fecha;
                char continuar;
                do {
                    pedirFecha(fecha);
                    fecha.ajustarFechaPago();
                    continuar = objValidacion.ingresoCaracter("Desea ingresar otra fecha? (s/n): ");
                } while (continuar == 's' || continuar == 'S');
                break;
            }
            case 2: {
                Fecha fecha;
                pedirFecha(fecha);
                objValidacion.mostrarSiguienteFeriadoYDiaHabil(fecha);
                break;
            }
            case 3:
                printf("\nSaliendo del programa...");
                break;
            default:
                printf("\nOpcion no valida. Intente de nuevo.");
        }
    } while (opcion != 3);
    return 0;
}

void pedirFecha(Fecha &fecha) {
    int anio, mes, dia;
    Anio objAnio;

    // Pedir y validar año
    do {
        anio = objValidacion.ingresoDatos("Ingrese el anio (1900-2025):");
        if (anio < 1900 || anio > 2025) {
            printf("\nEl anio ingresado esta fuera del rango permitido (1900-2025).");
        } else {
            if (objValidacion.validarAnio(anio)) {
                printf("\nEl anio ingresado es bisiesto.");
            } else {
                printf("\nEl anio ingresado no es bisiesto.");
            }
        }
    } while (anio < 1900 || anio > 2025);
    objAnio.setAnio(anio);
    objAnio.setAnioBisiesto(objValidacion.validarAnio(anio));
    fecha.setAnio(objAnio);

    // Pedir y validar mes
    do {
        mes = objValidacion.ingresoDatos("Ingrese el mes (1-12):");
        if (mes < 1 || mes > 12) {
            printf("\nEl mes ingresado no es valido.");
        }
    } while (mes < 1 || mes > 12);
    fecha.setMes(mes);

    // Pedir y validar día
    do {
        dia = objValidacion.ingresoDatos("Ingrese el dia:");
        bool diaValido = false;

        if (mes == 2) {
            diaValido = (objAnio.getAnioBisiesto() && dia >= 1 && dia <= 29) || (!objAnio.getAnioBisiesto() && dia >= 1 && dia <= 28);
        } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
            diaValido = dia >= 1 && dia <= 30;
        } else {
            diaValido = dia >= 1 && dia <= 31;
        }

        if (!diaValido) {
            printf("\nEl dia ingresado no es valido para el mes y anio especificados. ");
        } else {
            fecha.setDia(dia);
        }
    } while (dia < 1 || dia > 31 || 
             (mes == 2 && ((objAnio.getAnioBisiesto() && dia > 29) || (!objAnio.getAnioBisiesto() && dia > 28))) || 
             ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30));
}