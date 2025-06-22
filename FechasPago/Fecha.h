#ifndef FECHA_H
#define FECHA_H

#include "Anio.h"

class Fecha {
private:
    Anio anio;
    int mes;
    int dia;

public:
    Fecha();
    ~Fecha();

    Anio getAnio() const;
    void setAnio(Anio newAnio);
    int getMes() const;
    void setMes(int newMes);
    int getDia() const;
    void setDia(int newDia);

    bool esFinDeSemana() const;
    bool esFeriadoEcuador() const;
    void ajustarFechaPago();
    Fecha calcularCarnaval(int anio) const;
    Fecha calcularViernesSanto(int anio) const;
    void mostrarFecha() const;
};

#endif
