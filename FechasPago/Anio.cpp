#include "Anio.h"

Anio::Anio() {
    // Constructor
}

Anio::~Anio() {
    // Destructor
}

bool Anio::getAnioBisiesto() const {
    return anioBisiesto;
}

void Anio::setAnioBisiesto(bool value) {
    anioBisiesto = value;
}

int Anio::getAnio() const {
    return anio;
}

void Anio::setAnio(int newAnio) {
    anio = newAnio;
}

/*bool Anio::validarAnio(int anio) {
    const int MIN_ANIO = 1900;
    const int MAX_ANIO = 2025;

    if (anio < MIN_ANIO || anio > MAX_ANIO) {
        return false;
    }
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}*/
