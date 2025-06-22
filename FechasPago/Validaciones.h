#ifndef VALIDACION_H
#define VALIDACION_H
#include "Fecha.h"
class Validaciones {
private:

public:
    int ingresoDatos(const char* msj);
    int ingresoOpcionMenu(const char* msj);
    char ingresoCaracter(const char* msj);
    bool validarAnio(int anio);
    void mostrarSiguienteFeriadoYDiaHabil(Fecha fecha);
    void siguienteFeriadoYDiaHabil(Fecha fecha, Fecha &feriado, Fecha &diaHabil);
};

#endif